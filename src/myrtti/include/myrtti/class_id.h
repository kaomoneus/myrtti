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

#ifndef RTTI_CLASS_ID_H
#define RTTI_CLASS_ID_H

#include <iosfwd>
#include "crc/crc.hpp"

namespace myrtti {

using CRC = crc::CRC64;

struct class_id_t {
    constexpr class_id_t(const char* className) noexcept : value() {
        constexpr CRC engine;
        value = engine(className);
    }
    bool operator==(const class_id_t& rhs) const noexcept {
        return value == rhs.value;
    }
    bool operator<(const class_id_t& rhs) const noexcept {
        return value < rhs.value;
    }
    // May be one day we will need this operator as well. But so far just
    // let it sink commented into git.
    //
    //    bool operator==(uint64_t v) const noexcept {
    //        return value == v;
    //    }

    uint64_t value;
};

} // namespace myrtti

template<>
struct std::hash<myrtti::class_id_t> {
    uint64_t operator()(const myrtti::class_id_t& clid) const {
        return clid.value;
    }
};

std::ostream& operator <<(std::ostream& s, const myrtti::class_id_t& clid);

#endif