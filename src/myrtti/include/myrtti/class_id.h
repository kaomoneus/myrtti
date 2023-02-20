#ifndef RTTI_CLASS_ID_H
#define RTTI_CLASS_ID_H

namespace myrtti {

using class_id_t = unsigned;
constexpr class_id_t PREFIRST_CLASS_ID = 0;
constexpr class_id_t BAD_CLASS_ID = 0;

} // namespace myrtti
#endif