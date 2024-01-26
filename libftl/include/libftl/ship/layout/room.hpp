#ifndef LIBFTL_SHIP_LAYOUT_ROOM_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_ROOM_HPP_INCLUDED

#include <libftl/ship/layout/room_fwd.hpp> // IWYU pragma: keep
#include <libftl/ship/layout/room_id.hpp>
#include <libftl/ship/layout/tile_rect.hpp>

namespace libftl::ship::layout
{
struct room
{
  room(libftl::ship::layout::room_id const _id, libftl::ship::layout::tile_rect const _rect)
      : id_{_id}, rect_{_rect}
  {
  }

  libftl::ship::layout::room_id id_;

  libftl::ship::layout::tile_rect rect_;
};

}

#endif
