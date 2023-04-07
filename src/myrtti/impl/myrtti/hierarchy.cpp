#include "myrtti/hierarchy.h"
#include "myrtti/class_info.h"

namespace myrtti {
    class_id_t Hierarchy::resolveClassInfoId(const ClassInfo* classInfo) {
        return classInfo->getId();
    }
}