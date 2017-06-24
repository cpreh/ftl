#ifndef LIBFTL_SHIP_LAYOUT_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/door.hpp>
#include <libftl/ship/ellipse.hpp>
#include <libftl/ship/layout_fwd.hpp>
#include <libftl/ship/room.hpp>
#include <fcppt/strong_typedef.hpp>
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
		unsigned,
		2
	>
	offset_vector;

	FCPPT_MAKE_STRONG_TYPEDEF(
		bool,
		vertical
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
		libftl::ship::ellipse,
		room_list &&,
		door_list &&
	);

	offset_vector offset_;

	vertical vertical_;

	libftl::ship::ellipse ellipse_;

	room_list rooms_;

	door_list doors_;
};

}
}

#endif
