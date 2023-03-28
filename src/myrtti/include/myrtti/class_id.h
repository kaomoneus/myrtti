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

    struct hash {
        uint64_t operator()(const class_id_t& clid) {
            return clid.value;
        }
    };

    uint64_t value;
};

} // namespace myrtti

std::ostream& operator <<(std::ostream& s, const myrtti::class_id_t& clid);

#endif