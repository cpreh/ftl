#ifndef LIBFTL_SHIP_DOOR_HPP_INCLUDED
#define LIBFTL_SHIP_DOOR_HPP_INCLUDED

#include <libftl/ship/door_fwd.hpp>
#include <libftl/ship/room_id.hpp>
#include <libftl/ship/tile_pos.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace libftl
{
namespace ship
{

struct door
{
	typedef
	fcppt::optional::object<
		room_id
	>
	optional_room_id;

	FCPPT_MAKE_STRONG_TYPEDEF(
		bool,
		vertical
	);

	libftl::ship::tile_pos pos_;

	optional_room_id left_top_room_;

	optional_room_id bottom_right_room_;

	vertical vertical_;
};

}
}

#endif
