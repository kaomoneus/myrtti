#ifndef MYRTTI_RUNTIME_H
#define MYRTTI_RUNTIME_H

#include "myrtti/class_id.h"
#include "myrtti/dag.h"

#include <array>
#include <iostream>
#include <utility>

namespace myrtti {

struct ClassInfo {
    const char* name;

    ClassInfo(const char* name) : name(name) {}

    template<std::size_t N>
    ClassInfo(const char* name, const std::array<const ClassInfo*, N>& parents) : name(name) {
        std::cout << "Registered class: " << name << "\n";
        for (const auto& p : parents) {
            std::cout << "    parent: " << p->name << "\n";
        }
    }

    unsigned getId() { return id; }
private:
    class_id_t NextId() { static class_id_t id = PREFIRST_CLASS_ID; return ++id; }
    class_id_t id = NextId();
};

#define RTTI_CLASS_NAME(cn) \
    static const char* className() { return #cn; }


struct Object {
    RTTI_CLASS_NAME(Object);
    static const ClassInfo& info() { static ClassInfo v(className()); return v; }

    // We intentinally keep it public:
    const ClassInfo* rtti = &info();
};

// Problems:
// 1. If we inharit RTTI from Parents, then we can't
// use parents with non-default constructors.
// 2. If we let T to inharit parents by itself, then we get T::info ambiguity.
// 3. If we move 'info' into T, that we're out of "parents" clause,
//    so then for RTTI definition we should not only to provide a tricky parent,
//    but also write something in declaration body.

template <class T, class ...Parents>
struct RTTI : virtual Parents... {
    RTTI() { this->rtti = &info(); }

    static const ClassInfo& info() {
        static ClassInfo v(            
            T::className(),
            std::array<const ClassInfo*, sizeof...(Parents)>({
                &Parents::info()...
            })
        );
        return v;
    }
};

} // namespace myrtti

#endif
