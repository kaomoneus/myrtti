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