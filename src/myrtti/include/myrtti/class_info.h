#ifndef MYRTTI_CLASS_INFO_H
#define MYRTTI_CLASS_INFO_H

#include "myrtti/class_id.h"
#include "myrtti/hierarchy.h"

#include <array>

namespace myrtti {

struct ClassInfo {
    const char* name;

    ClassInfo(const char* name, class_id_t classId) : name(name), id(classId) {
        Hierarchy::instance()->add(this, std::array<class_id_t, 0>());
    }

    template<typename ArrayT>
    ClassInfo(const char* name, class_id_t classId, const ArrayT& parents)
    : name(name), id(classId) {
        // std::cout << "Registered class: " << name << "\n";
        // for (const ClassInfo* p : parents) {
        //     std::cout << "    parent: " << p->name << "\n";
        // }
        Hierarchy::instance()->add(this, parents);
    }

    class_id_t getId() const { return id; }
private:
    class_id_t id;
};
}

#endif