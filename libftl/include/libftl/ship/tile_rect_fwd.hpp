#ifndef LIBFTL_SHIP_TILE_RECT_FWD_HPP_INCLUDED
#define LIBFTL_SHIP_TILE_RECT_FWD_HPP_INCLUDED

#include <libftl/ship/tile_coordinate.hpp>
#include <fcppt/math/box/rect_fwd.hpp>


namespace libftl
{
namespace ship
{

typedef
fcppt::math::box::rect<
	libftl::ship::tile_coordinate
>
tile_rect;

}
}

#endif
