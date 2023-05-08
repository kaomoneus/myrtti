// Copyright 2023 Stepan Dyatkovskiy at Kaspersky Lab.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MYRTTI_RUNTIME_H
#define MYRTTI_RUNTIME_H

// Uncomment if you want to use std::unordered_map for crossPtrs
// #define CROSS_PTRS_UNORDERED_MAP

#include "utils/macros/va_arg_prefix.h"

#include "myrtti/class_id.h"
#include "myrtti/class_info.h"
#include "myrtti/hierarchy.h"

#include <array>
#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <utility>

#ifndef CROSS_PTRS_UNORDERED_MAP
#include <map>
#else
#include <unordered_map>
#endif

#include <type_traits>

namespace myrtti {

struct Object {
    virtual ~Object() = default;

    Object() {
        reportCrossPtrs();
    }

    static constexpr class_id_t class_id() { return {"myrtti::Object"}; }
    static const ClassInfo* info() {
        static ClassInfo v("myrtti::Object", class_id());
        return &v;
    }

    // We intentinally keep rtti field public:
    const ClassInfo* rtti = info();

    void reportCrossPtrs() {
        #if defined(CROSS_PTRS_UNORDERED_MAP) && defined(DEBUG_REPORT_CROSS_PTRS)
        std::size_t bc = crossPtrs.bucket_count();
        std::cout << "CrossPtrs (" << rtti->name << "):\n";
        std::cout << "  Bucket count: " << bc << "\n";
        std::cout << "  Max load factor: " << crossPtrs.max_load_factor() << "\n";
        for (std::size_t bucket = 0; bucket!=bc; ++bucket) {
            std::size_t bs = crossPtrs.bucket_size(bucket);
            std::cout << "    Bucket[" << bucket << "] size: " << crossPtrs.bucket_size(bucket) << "\n";
            std::size_t j = 0;
            for (auto item = crossPtrs.begin(bucket); item!= crossPtrs.end(bucket); ++item, ++j) {
                const auto* classInfo = Hierarchy::instance()->getClassInfo(item->first);
                std::cout << "        item[" << j << "]: " << classInfo << "\n";
            }
        }
        #endif
    }

    //
    // dyn_cast
    //

    template<class T, std::enable_if_t<!std::is_pointer_v<T>, bool> = true>
    T& cast() {
        using TT = std::add_const_t<T&>;
        return const_cast<T&>(
            const_cast<const Object*>(this)->cast<TT>()
        );
    }

    template<class T, std::enable_if_t<std::is_pointer_v<T>, bool> = true>
    T cast() {
        using TT = std::add_const_t<T>;
        return const_cast<T>(
            const_cast<const Object*>(this)->cast<TT>()
        );
    }

    // NOTE: we can not replace `enable_if` with `if constexpr`, because
    //   method prototypes are not unified enough.
    //   * If user calls `cast<SomeType>` then we should return reference to existing object.
    //   * If user calls `cast<SomeType*>` then we should return a copy of discovered pointer.
    //   Of course we can use some super logic and craft smth like
    //      `ret_type<T> cast() {...}`
    //   but ret_type will be quite complicated as well.
    //   Keeping in mind, that we would had two `if constexpr` branches, we won't make resulting code any smaller.
    template<class T, std::enable_if_t<!std::is_pointer_v<T>, bool> = true>
    const T& cast() const {
        using TT = std::remove_reference_t<T>;
        auto found = this->crossPtrs.find(TT ::class_id());
        if (/*[[likely]]*/ found != end(this->crossPtrs)) {
            return *static_cast<TT*>(found->second);
        }
        // Unable to cast, unable to return null, panic.
        abort();
    }

    template<class T, std::enable_if_t<std::is_pointer_v<T>, bool> = true>
    T cast() const {
        using TT = std::remove_pointer_t<T>;
        auto found = this->crossPtrs.find(TT::class_id());
        if (found != end(this->crossPtrs))
            return static_cast<T>(found->second);
        return nullptr;
    }

protected:
    template<class T>
    friend struct RTTI;

    template<class T, class From>
    friend T try_static_cast(From* from);

    // Note: rtti field should be initialized before crossPtrs.
    // Note #2: Even though unordered_map seems to be faster in average, but
    //    in case of hash collisions performance might drop N times.
    //    so far we have switched to std::map for it seems to be more stable,
    //    showing similar results for our case.

    #ifndef CROSS_PTRS_UNORDERED_MAP
    std::map<class_id_t, void*> crossPtrs{{class_id(), this}};
    #else
    std::unordered_map<class_id_t, void*> crossPtrs{{class_id(), this}};
    #endif
};

// Problems:
// 1. If we inharit RTTI from Parents, then we can't
// use parents with non-default constructors.
// 1.1. Here we also could create:
//    template<class ParentSrcs..>
//    RTTI(ParentSrcs... srcs) : ParentSrcs(srcs)... {}
//    But what happens if some of parents have shared ancestor?
//    So we bump into unspecified behaviour.
// 2. If we let T to inharit parents by itself, then we get T::info ambiguity.
// 3. If we move 'info' into T, that we're out of "parents" clause,
//    so then for RTTI definition we should not only to provide a tricky parent,
//    but also write something in declaration body.

template <class Class>
struct RTTI : virtual Object {
    RTTI() {
        auto *superSelf = static_cast<Class*>(this);
        this->rtti = Class::info();
        this->crossPtrs[Class::class_id()] = superSelf;
        reportCrossPtrs();
    }
};

template<class T>
using strip_type = std::remove_pointer_t<
    std::remove_const_t<
        std::remove_reference_t<T>
    >
>;

template<class B, class T>
using is_base_of = std::is_base_of<strip_type<B>, strip_type<T>>;

#define MYRTTI_UNIQUE_NAME(cn) #cn, __FILE__, __LINE__

#define DEFINE_RTTI(cn, ...) \
    static constexpr myrtti::class_id_t class_id() { return {MYRTTI_UNIQUE_NAME(cn)}; }                       \
    static const ::myrtti::ClassInfo* info() {                                                         \
        static std::unique_ptr<myrtti::ClassInfo> p = myrtti::ClassInfo::create<cn, __VA_ARGS__>(#cn); \
        return p.get(); \
    }

#define MYRTTI_ESC(...) __VA_ARGS__

#define with_rtti_root(class_or_struct, name) \
struct name : public ::myrtti::RTTI<name> {          \
    public:                                   \
    DEFINE_RTTI(name, ::myrtti::Object);      \
    MYRTTI_DEFAULT_ACCESS(class_or_struct)    \

#define MYRTTI_DEFAULT_ACCESS(class_or_struct) MYRTTI_CAT(__MYRTTI_DEFAULT_ACCESS_, class_or_struct)
#define __MYRTTI_DEFAULT_ACCESS_class private:
#define __MYRTTI_DEFAULT_ACCESS_struct public:

#define with_rtti(class_or_struct, name, parent)                        \
    class_or_struct name : public parent, public ::myrtti::RTTI<name> { \
    public:                                                             \
    DEFINE_RTTI(name, parent);                                          \
    MYRTTI_DEFAULT_ACCESS(class_or_struct)                              \

#define with_rtti_parents(class_or_struct, name, parents)               \
    class_or_struct name :                                              \
    MYRTTI_ADD_VA_PREFIX(public, MYRTTI_ESC parents),                   \
    public ::myrtti::RTTI<name> {                                       \
    public:                                                             \
    DEFINE_RTTI(name, MYRTTI_ESC parents);                              \
    MYRTTI_DEFAULT_ACCESS(class_or_struct)                              \

#define with_rtti_vparents_parents(class_or_struct, name, virtual_parents, parents)              \
    class_or_struct name :                                                                       \
        MYRTTI_ADD_VA_PREFIX(public, MYRTTI_ADD_VA_PREFIX(virtual, MYRTTI_ESC virtual_parents)), \
        MYRTTI_ADD_VA_PREFIX(public, MYRTTI_ESC parents),                                        \
        public ::myrtti::RTTI<name> {                                                            \
    public:                                                                                      \
    DEFINE_RTTI(name, MYRTTI_ESC virtual_parents, MYRTTI_ESC parents);                           \
    MYRTTI_DEFAULT_ACCESS(class_or_struct)                                                       \

#define with_rtti_vparents(class_or_struct, name, virtual_parents)                               \
    class_or_struct name :                                                                       \
        MYRTTI_ADD_VA_PREFIX(public, MYRTTI_ADD_VA_PREFIX(virtual, MYRTTI_ESC virtual_parents)), \
        public ::myrtti::RTTI<name> {                                                            \
    public:                                                                                      \
    DEFINE_RTTI(name, MYRTTI_ESC virtual_parents);                                               \
    MYRTTI_DEFAULT_ACCESS(class_or_struct)                                                       \


#define with_rtti_end() }

template<class T, std::enable_if_t<std::is_pointer<T>::value, bool> = true>
inline T dyn_cast(Object* o) {return o->cast<T>();}

template<class T, std::enable_if_t<!std::is_pointer<T>::value, bool> = true>
inline T& dyn_cast(Object& o) {return o.cast<T>();}

template<class T>
inline bool isa(const Object* o) { return T::class_id() == o->rtti->getId();}
template<class T>
inline bool isa(const Object& o) { return T::class_id() == o.rtti->getId();}

//
// try_static_cast
//
template<class T, class From>
T try_static_cast(From* from) {
    static_assert(std::is_pointer_v<T> && "T must be a pointer type.");
    static_assert(From::class_id() != Object::class_id() && "Unable static_cast from virtual Object class.");

    // TODO: for debug modes also add verification whether there is straight static (non-virtual) inheritance line
    //   between From and To.
    using TT = std::remove_pointer_t<T>;
    if (from->crossPtrs.count(TT::class_id()))
        return static_cast<T>(from);
    return nullptr;
}

} // namespace myrtti

#endif
