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

    static constexpr class_id_t class_id = class_id_t("Object");
    static const ClassInfo* info() {
        static ClassInfo v("Object", class_id);
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

    // TODO: combine "cast" and "cast() const" ... using const_cast?
    // TODO: introduce "smart_static_cast" to compete with UE for single inharitance schema.
    //    perhaps we also could do constexpr check whether we're casting from virtual
    //    class? Then we need constexpr collection of virtual bases.
    template<class T, std::enable_if_t<!std::is_pointer<T>::value, bool> = true>
    T& cast() {
        // TODO: Validate that T::info() takes longer time for polymorphic types.
        auto found = this->crossPtrs.find(T::class_id);
        if (/*[[likely]]*/ found != end(this->crossPtrs)) {
            return *static_cast<T*>(found->second);
        }
        // Unable to cast, unable to return null, panic.
        abort();
    }

    template<class T, std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    T cast() {
        using _T = std::remove_pointer_t<T>;
        auto found = this->crossPtrs.find(_T::class_id);
        if (/*[[likely]]*/ found != end(this->crossPtrs)) {
            return static_cast<T>(found->second);
        }
        return nullptr;
    }

    template<class T, std::enable_if_t<!std::is_pointer<T>::value, bool> = true>
    const T& cast() const {
        auto found = this->crossPtrs.find(T::class_id);
        if (/*[[likely]]*/ found != end(this->crossPtrs)) {
            return *static_cast<T*>(found->second);
        }
        // Unable to cast, unable to return null, panic.
        abort();
    }

    template<class T, std::enable_if_t<std::is_pointer<T>::value, bool> = true>
    const T cast() const {
        using _T = std::remove_pointer_t<T>;
        auto found = this->crossPtrs.find(_T::class_id);
        if (found != end(this->crossPtrs))
            return static_cast<T>(found->second);
        return nullptr;
    }

protected:
    template<class T>
    friend struct RTTI;

    // Note: rtti field should be initialized before crossPtrs.
    // Note #2: Even though unordered_map seems to be faster in average, but
    //    in case of hash collisions performance might drop N times.
    //    so far we have switched to std::map for it seems to be more stable,
    //    showing similar results for our case.

    #ifndef CROSS_PTRS_UNORDERED_MAP
    std::map<class_id_t, void*> crossPtrs{{class_id, this}};
    #else
    std::unordered_map<class_id_t, void*> crossPtrs{{class_id, this}};
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
        this->crossPtrs[Class::class_id] = superSelf;
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

// this is a custom make_array implementation
template<class ...Parents>
static std::array<class_id_t, sizeof...(Parents)>
mk_class_ids() {
    return {Parents::class_id...};
}

// We use constexpr crc64 implementation, written by Sam Belliveau
// https://gist.github.com/Sam-Belliveau/72ba4a8710324ce7a1ac1789d64ec831
#define DEFINE_RTTI(cn, ...) \
    static constexpr myrtti::class_id_t class_id = myrtti::class_id_t(#cn); \
    static const ::myrtti::ClassInfo* info() { \
        static myrtti::ClassInfo v(#cn, class_id, ::myrtti::mk_class_ids<__VA_ARGS__>()); \
        return &v; \
    }

#define RTTI_ESC(...) __VA_ARGS__

#define RTTI_STRUCT_AND_TRAITS_BEGIN(name, runtime_parents, traits) \
struct name : RTTI_ESC traits, RTTI_ESC runtime_parents, ::myrtti::RTTI<name> { \
    DEFINE_RTTI(name, RTTI_ESC(runtime_parents)); \

#define RTTI_STRUCT_ROOT_BEGIN(name) \
struct name : ::myrtti::RTTI<name> { \
    DEFINE_RTTI(name, ::myrtti::Object); \

#define RTTI_STRUCT_BEGIN(name, runtime_parents) \
struct name : RTTI_ESC runtime_parents, ::myrtti::RTTI<name> { \
    DEFINE_RTTI(name, RTTI_ESC runtime_parents); \

#define RTTI_STRUCT_END() };

#define class_rtti(name, parent) \
    class name : public parent, ::myrtti::RTTI<name> { \
    DEFINE_RTTI(name, parent);   \

#define class_rtti_parents(name, parents)  \
    class name :                           \
        VA_PREF(public, RTTI_ESC parents), \
        public ::myrtti::RTTI<name> {      \
    public:                                \
    DEFINE_RTTI(name, RTTI_ESC parents);   \
    private:                               \

#define class_rtti_vparents_parents(name, virtual_parents, parents)  \
    class name :                                                     \
        VA_PREF(public, VA_PREF(virtual, RTTI_ESC virtual_parents)), \
        VA_PREF(public, RTTI_ESC parents),                           \
        public ::myrtti::RTTI<name> {                                \
    public:                                                          \
    DEFINE_RTTI(name, RTTI_ESC virtual_parents, RTTI_ESC parents);   \
    private:                                                         \

#define class_rtti_vparents(name, virtual_parents)                   \
    class name :                                                     \
        VA_PREF(public, VA_PREF(virtual, RTTI_ESC virtual_parents)), \
        public ::myrtti::RTTI<name> {                                \
    public:                                                          \
    DEFINE_RTTI(name, RTTI_ESC virtual_parents);                     \
    private:                                                         \

#define class_rtti_end() }

template<class T, std::enable_if_t<std::is_pointer<T>::value, bool> = true>
inline T dyn_cast(Object* o) {return o->cast<T>();}

template<class T, std::enable_if_t<!std::is_pointer<T>::value, bool> = true>
inline T& dyn_cast(Object& o) {return o.cast<T>();}


template<class T>
inline bool isa(const Object* o) { return T::class_id == o->rtti->getId();}
template<class T>
inline bool isa(const Object& o) { return T::class_id == o.rtti->getId();}

} // namespace myrtti

#endif
