#ifndef LIBFTL_SHIP_LAYOUT_ROOM_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_ROOM_HPP_INCLUDED

#include <libftl/ship/layout/room_fwd.hpp>
#include <libftl/ship/layout/room_id.hpp>
#include <libftl/ship/layout/tile_rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace ship
{
namespace layout
{

struct room
{
	room(
		libftl::ship::layout::room_id const _id,
		libftl::ship::layout::tile_rect _rect
	)
	:
		id_{
			_id
		},
		rect_{
			std::move(
				_rect
			)
		}
	{
	}

	libftl::ship::layout::room_id id_;

	libftl::ship::layout::tile_rect rect_;
};

}
}
}

#endif
