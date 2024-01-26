#ifndef LIBFTL_ROOM_TYPE_HPP_INCLUDED
#define LIBFTL_ROOM_TYPE_HPP_INCLUDED

#include <libftl/room/type_fwd.hpp> // IWYU pragma: keep

namespace libftl::room
{
enum class type
{
  pilot,
  sensors,
  doors,
  shields,
  engines,
  medbay,
  clonebay,
  oxygen,
  teleporter,
  mind,
  hacking,
  drones,
  weapons,
  battery,
  cloaking,
  artillery
};

}

#endif
