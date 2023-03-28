#include <sstream>
#include <iomanip>

#include "myrtti/class_id.h"

using namespace std;
using namespace myrtti;

ostream& operator <<(ostream& s, const class_id_t& clid) {
    // TODO: It doesn't look like an optimal way to format 0000-babe-cafe-babe

    std::ostringstream ostrm;

    uint64_t v = clid.value;

    ostrm << setfill('0') << setw(4) << right << hex
          << ((v & 0xffff000000000000) >> 48);
    v <<= 16;

    for (int i = 0; i!=3; ++i,v<<=16) {
        ostrm << setw(1) << "-";
        ostrm << setw(4) << ((v & 0xffff000000000000) >> 48);
    }
    s << ostrm.str();
    return s;
}