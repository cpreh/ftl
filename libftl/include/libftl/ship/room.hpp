#ifndef LIBFTL_SHIP_ROOM_HPP_INCLUDED
#define LIBFTL_SHIP_ROOM_HPP_INCLUDED

#include <libftl/ship/room_fwd.hpp>
#include <libftl/ship/room_id.hpp>
#include <libftl/ship/tile_rect.hpp>


namespace libftl
{
namespace ship
{

struct room
{
	libftl::ship::room_id id_;

	libftl::ship::tile_rect rect_;
};

}
}

#endif
