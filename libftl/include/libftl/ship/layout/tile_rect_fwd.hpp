#ifndef LIBFTL_SHIP_LAYOUT_TILE_RECT_FWD_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_TILE_RECT_FWD_HPP_INCLUDED

#include <libftl/ship/layout/tile_coordinate.hpp>
#include <fcppt/math/box/rect_fwd.hpp>

namespace libftl
{
namespace ship
{
namespace layout
{
using tile_rect = fcppt::math::box::rect<libftl::ship::layout::tile_coordinate>;

}
}
}

#endif
