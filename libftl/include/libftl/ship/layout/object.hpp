#ifndef LIBFTL_SHIP_LAYOUT_OBJECT_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_OBJECT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/layout/door.hpp>
#include <libftl/ship/layout/ellipse.hpp>
#include <libftl/ship/layout/object_fwd.hpp>
#include <libftl/ship/layout/room.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace ship
{
namespace layout
{

struct object
{
	typedef
	fcppt::math::vector::static_<
		fcppt::optional::object<
			unsigned
		>,
		2
	>
	offset_vector;

	FCPPT_MAKE_STRONG_TYPEDEF(
		int,
		vertical
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		fcppt::optional::object<
			int
		>,
		horizontal
	);

	typedef
	std::vector<
		libftl::ship::layout::room
	>
	room_list;

	typedef
	std::vector<
		libftl::ship::layout::door
	>
	door_list;

	LIBFTL_DETAIL_SYMBOL
	object(
		offset_vector,
		vertical,
		horizontal,
		libftl::ship::layout::ellipse,
		room_list &&,
		door_list &&
	);

	offset_vector offset_;

	vertical vertical_;

	horizontal horizontal_;

	libftl::ship::layout::ellipse ellipse_;

	room_list rooms_;

	door_list doors_;
};

}
}
}

#endif
