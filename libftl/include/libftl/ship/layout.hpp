#ifndef LIBFTL_SHIP_LAYOUT_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/door.hpp>
#include <libftl/ship/ellipse.hpp>
#include <libftl/ship/layout_fwd.hpp>
#include <libftl/ship/room.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace ship
{

struct layout
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
		libftl::ship::room
	>
	room_list;

	typedef
	std::vector<
		libftl::ship::door
	>
	door_list;

	LIBFTL_DETAIL_SYMBOL
	layout(
		offset_vector,
		vertical,
		horizontal,
		libftl::ship::ellipse,
		room_list &&,
		door_list &&
	);

	offset_vector offset_;

	vertical vertical_;

	horizontal horizontal_;

	libftl::ship::ellipse ellipse_;

	room_list rooms_;

	door_list doors_;
};

}
}

#endif
