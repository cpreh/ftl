#ifndef LIBFTL_SPRITE_OBJECT_HPP_INCLUDED
#define LIBFTL_SPRITE_OBJECT_HPP_INCLUDED

#include <libftl/sprite/choices.hpp>
#include <sge/sprite/object.hpp>


namespace libftl
{
namespace sprite
{

typedef
sge::sprite::object<
	libftl::sprite::choices
>
object;

}
}

#endif
