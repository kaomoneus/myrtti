#ifndef MYRTTI_RUNTIME_H
#define MYRTTI_RUNTIME_H

#include "myrtti/class_id.h"
#include "myrtti/hierarchy.h"

#include <array>
#include <iostream>
#include <utility>
#include <unordered_map>

namespace myrtti {

struct ClassInfo {
    const char* name;

    // this is a custom make_array implementation
    template<class ...Parents>
    static std::array<const ClassInfo*, sizeof...(Parents)>
    mk_class_info_array() {
        return {&Parents::info()...};
    }

    ClassInfo(const char* name) : name(name) {
        Hierarchy::instance()->add(this, std::array<const ClassInfo*, 0>());
    }

    template<typename ArrayT>
    ClassInfo(const char* name, const ArrayT& parents) : name(name) {
        // std::cout << "Registered class: " << name << "\n";
        for (const ClassInfo* p : parents) {
            // std::cout << "    parent: " << p->name << "\n";
        }
        Hierarchy::instance()->add(this, parents);
    }

    unsigned getId() { return id; }
private:
    class_id_t NextId() { static class_id_t id = PREFIRST_CLASS_ID; return ++id; }
    class_id_t id = NextId();
};

struct Object {
    // FIXME: must return ClassInfo* (not reference)
    static const ClassInfo& info() {
        static ClassInfo v("Object");
        return v;
    }

    // We intentinally keep rtti field public:
    const ClassInfo* rtti = &info();

    template<class T>
    T* cast() {
        auto found = this->crossPtrs.find(&T::info());
        if (/*[[likely]]*/ found != end(this->crossPtrs))
            // FIXME: cross-cast won't work! Need to use hierarchy.
            return static_cast<T*>(found->second);
        return nullptr;
    }

    template<class T>
    const T* cast() const {
        auto &tInfo = T::info();
        auto found = this->crossPtrs.find(&tInfo);
        if (found != end(this->crossPtrs))
            return static_cast<T*>(found->second);
        return nullptr;
    }
protected:
    template<class T>
    friend class RTTI;

    // TODO: randomize hashing routine.
    std::unordered_map<const ClassInfo*, void*> crossPtrs;
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

template <class T>
struct RTTI : virtual Object {
    RTTI() {
        auto *superSelf = static_cast<T*>(this);
        this->rtti = &T::info();
        this->crossPtrs[this->rtti] = superSelf;
    }
};

#define DEFINE_RTTI(cn, ...) \
    static const ClassInfo& info() { \
        static ClassInfo v(#cn, ClassInfo::mk_class_info_array<__VA_ARGS__>()); \
        return v; \
    } \

} // namespace myrtti

#define RTTI_ESC(...) __VA_ARGS__

#define RTTI_STRUCT_AND_TRAITS_BEGIN(name, runtime_parents, traits) \
struct name : RTTI_ESC traits, RTTI_ESC runtime_parents, RTTI<name> { \
    DEFINE_RTTI(name, RTTI_ESC(runtime_parents)); \

#define RTTI_STRUCT_BEGIN(name, runtime_parents) \
struct name : RTTI_ESC runtime_parents, RTTI<name> { \
    DEFINE_RTTI(name, RTTI_ESC runtime_parents); \

#define RTTI_STRUCT_END() };


#endif
