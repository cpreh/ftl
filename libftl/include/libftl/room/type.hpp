#ifndef LIBFTL_ROOM_TYPE_HPP_INCLUDED
#define LIBFTL_ROOM_TYPE_HPP_INCLUDED

#include <libftl/room/type_fwd.hpp>


namespace libftl
{
namespace room
{

enum class type
{
	pilot,
	sensors,
	doors,
	shields,
	engines,
	medbay,
	clonebay,
	oxygen,
	teleporter,
	mindcontrol,
	hacking,
	dronecontrol,
	weapons,
	battery,
	cloaking
};

}
}

#endif
