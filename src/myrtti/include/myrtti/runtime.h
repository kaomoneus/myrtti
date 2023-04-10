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

#include "myrtti/class_id.h"
#include "myrtti/class_info.h"

#include <array>
#include <cstdlib>
#include <iosfwd>
#include <iostream>
#include <utility>
#include <unordered_map>
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
        #ifdef DEBUG_REPORT_CROSS_PTRS
        std::size_t bc = crossPtrs.bucket_count();
        std::cout << "CrossPtrs (" << rtti->name << "):\n";
        std::cout << "  Bucket count: " << bc << "\n";
        for (std::size_t bucket = 0; bucket!=bc; ++bucket) {
            std::size_t bs = crossPtrs.bucket_size(bucket);
            std::cout << "    Bucket[" << bucket << "] size: " << crossPtrs.bucket_size(bucket) << "\n";
            std::size_t j = 0;
            for (auto item = crossPtrs.begin(bucket); item!= crossPtrs.end(bucket); ++item, ++j) {
                std::cout << "        item[" << j << "]: " << item->first->name << "\n";
            }
        }
        #endif
    }

    //
    // dyn_cast
    //

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
    friend class RTTI;

    // Note: rtti field should be initialized before crossPtrs.
    std::unordered_map<class_id_t, void*> crossPtrs{{class_id, this}};
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
    static constexpr class_id_t class_id = class_id_t(#cn); \
    static const ::myrtti::ClassInfo* info() { \
        static ClassInfo v(#cn, class_id, ::myrtti::mk_class_ids<__VA_ARGS__>()); \
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

template<class T, std::enable_if_t<std::is_pointer<T>::value, bool> = true>
inline T dyn_cast(Object* o) {return o->cast<T>();}

template<class T, std::enable_if_t<!std::is_pointer<T>::value, bool> = true>
inline T& dyn_cast(Object& o) {return o.cast<T>();}


template<class T>
inline bool isa(const Object* o) { return T::class_id == o->rtti->getId();}
template<class T>
inline bool isa(const Object& o) { return T::class_id == o.rtti->getId();}

} // namespace myrtti

std::ostream& operator <<(std::ostream& s, const myrtti::ClassInfo* clid);
std::ostream& operator <<(std::ostream& s, const myrtti::ClassInfo& clid);

#endif
