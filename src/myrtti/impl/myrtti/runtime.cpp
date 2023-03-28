#include <sstream>
#include <iomanip>

#include "myrtti/runtime.h"

using namespace std;
using namespace myrtti;

std::ostream& operator <<(std::ostream& s, const myrtti::ClassInfo* clid) {
    s << clid->name << "(id:" << clid->getId() << ")";
    return s;
}

std::ostream& operator <<(std::ostream& s, const myrtti::ClassInfo& clid) {
    s << &clid;
    return s;
}
