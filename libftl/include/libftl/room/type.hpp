#ifndef LIBFTL_ROOM_TYPE_HPP_INCLUDED
#define LIBFTL_ROOM_TYPE_HPP_INCLUDED

#include <libftl/room/type_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace libftl::room
{
enum class type : std::uint8_t
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
