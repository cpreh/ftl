#ifndef LIBFTL_SHIP_LAYOUT_TILE_POS_FWD_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_TILE_POS_FWD_HPP_INCLUDED

#include <libftl/ship/layout/tile_coordinate.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace libftl
{
namespace ship
{
namespace layout
{

using
tile_pos
=
fcppt::math::vector::static_<
	libftl::ship::layout::tile_coordinate,
	2
>;

}
}
}

#endif
