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