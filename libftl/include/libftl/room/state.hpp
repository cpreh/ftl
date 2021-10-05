#ifndef LIBFTL_ROOM_STATE_HPP_INCLUDED
#define LIBFTL_ROOM_STATE_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/room/state_fwd.hpp>
#include <libftl/room/system.hpp>
#include <libftl/ship/layout/room.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace libftl::room
{
struct state
{
  LIBFTL_DETAIL_SYMBOL
  state(fcppt::optional::object<libftl::room::system> &&, libftl::ship::layout::room);

  fcppt::optional::object<libftl::room::system> system_;

  libftl::ship::layout::room layout_;
};

}

#endif
