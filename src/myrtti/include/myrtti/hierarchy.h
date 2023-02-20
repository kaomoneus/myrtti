#ifndef MYRTTI_HIERARCHY_H
#define MYRTTI_HIERARCHY_H

#include "myrtti/class_id.h"
#include "myrtti/dag.h"

namespace myrtti {

struct Hierarchy {
private:
    DAG<class_id_t> dag;
};

} // namespace myrtti

#endif