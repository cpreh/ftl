#ifndef LIBFTL_IMPL_ROOM_DRAW_HPP_INCLUDED
#define LIBFTL_IMPL_ROOM_DRAW_HPP_INCLUDED

#include <libftl/ship/layout/object_fwd.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/sprite/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace room
{

std::vector<
	libftl::sprite::object
>
draw(
	libftl::sprite::images &,
	libftl::ship::layout::object const &
);

}
}
}

#endif
