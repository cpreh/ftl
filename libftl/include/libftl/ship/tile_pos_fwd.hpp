#ifndef LIBFTL_SHIP_TILE_POS_FWD_HPP_INCLUDED
#define LIBFTL_SHIP_TILE_POS_FWD_HPP_INCLUDED

#include <libftl/ship/tile_coordinate.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace libftl
{
namespace ship
{

typedef
fcppt::math::vector::static_<
	libftl::ship::tile_coordinate,
	2
>
tile_pos;

}
}

#endif
