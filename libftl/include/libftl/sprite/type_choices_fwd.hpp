#ifndef LIBFTL_SPRITE_TYPE_CHOICES_FWD_HPP_INCLUDED
#define LIBFTL_SPRITE_TYPE_CHOICES_FWD_HPP_INCLUDED

#include <sge/sprite/config/float_type_fwd.hpp>
#include <sge/sprite/config/type_choices_fwd.hpp>
#include <sge/sprite/config/unit_type_fwd.hpp>


namespace libftl
{
namespace sprite
{

using
type_choices
=
sge::sprite::config::type_choices<
	sge::sprite::config::unit_type<
		int
	>,
	sge::sprite::config::float_type<
		float
	>
>;

}
}

#endif
