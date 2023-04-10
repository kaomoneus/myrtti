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