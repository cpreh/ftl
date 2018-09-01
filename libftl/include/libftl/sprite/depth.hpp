#ifndef LIBFTL_SPRITE_DEPTH_HPP_INCLUDED
#define LIBFTL_SPRITE_DEPTH_HPP_INCLUDED

#include <libftl/sprite/depth_fwd.hpp>


namespace libftl
{
namespace sprite
{

enum class depth
{
	// TODO
	background,
	base,
	floor,
	tile_background,
	tile,
	crew,
	something,
	fcppt_maximum = something
};

}
}

#endif
