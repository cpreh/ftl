#ifndef LIBFTL_SHIP_LAYOUT_ROOM_ID_SIGNED_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_ROOM_ID_SIGNED_HPP_INCLUDED

#include <libftl/ship/layout/room_id.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::ship::layout
{
using room_id_signed = std::make_signed_t<libftl::ship::layout::room_id::value_type>;
}

#endif
