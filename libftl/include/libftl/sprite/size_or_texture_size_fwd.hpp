#ifndef LIBFTL_SPRITE_SIZE_OR_TEXTURE_SIZE_FWD_HPP_INCLUDED
#define LIBFTL_SPRITE_SIZE_OR_TEXTURE_SIZE_FWD_HPP_INCLUDED

#include <libftl/sprite/type_choices_fwd.hpp>
#include <sge/sprite/types/size_or_texture_size_fwd.hpp>


namespace libftl
{
namespace sprite
{

typedef
sge::sprite::types::size_or_texture_size<
	libftl::sprite::type_choices
>
size_or_texture_size;

}
}

#endif
