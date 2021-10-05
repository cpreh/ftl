#ifndef LIBFTL_SHIP_LAYOUT_DOOR_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_DOOR_HPP_INCLUDED

#include <libftl/ship/layout/door_fwd.hpp>
#include <libftl/ship/layout/room_id.hpp>
#include <libftl/ship/layout/tile_pos.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace libftl::ship::layout
{
struct door
{
  using optional_room_id = fcppt::optional::object<room_id>;

  FCPPT_MAKE_STRONG_TYPEDEF(bool, vertical);

  FCPPT_MAKE_STRONG_TYPEDEF(optional_room_id, left_top_room);

  FCPPT_MAKE_STRONG_TYPEDEF(optional_room_id, bottom_right_room);

  door(
      libftl::ship::layout::tile_pos const _pos,
      left_top_room const _left_top_room,
      bottom_right_room _bottom_right_room,
      vertical const _vertical)
      : pos_{_pos},
        left_top_room_{_left_top_room},
        bottom_right_room_{_bottom_right_room},
        vertical_{_vertical}
  {
  }

  libftl::ship::layout::tile_pos pos_;

  left_top_room left_top_room_;

  bottom_right_room bottom_right_room_;

  vertical vertical_;
};

}

#endif
