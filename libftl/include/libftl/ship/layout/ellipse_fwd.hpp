#ifndef LIBFTL_SHIP_LAYOUT_ELLIPSE_FWD_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_ELLIPSE_FWD_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/math/box/rect_fwd.hpp>


namespace libftl
{
namespace ship
{
namespace layout
{

FCPPT_MAKE_STRONG_TYPEDEF(
	fcppt::math::box::rect<
		int
	>,
	ellipse
);

}
}
}

#endif
