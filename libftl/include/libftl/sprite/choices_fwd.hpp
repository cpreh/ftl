#ifndef LIBFTL_SPRITE_CHOICES_FWD_HPP_INCLUDED
#define LIBFTL_SPRITE_CHOICES_FWD_HPP_INCLUDED

#include <libftl/sprite/color_format.hpp>
#include <libftl/sprite/type_choices_fwd.hpp>
#include <libftl/sprite/detail/depth_element_fwd.hpp>
#include <sge/sprite/config/choices_fwd.hpp>
#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/config/pos_fwd.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/with_color_fwd.hpp>
#include <sge/sprite/config/with_texture_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace sprite
{

typedef
sge::sprite::config::choices<
	libftl::sprite::type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::normal_size<
		sge::sprite::config::texture_size_option::maybe
	>,
	brigand::list<
		sge::sprite::config::with_color<
			libftl::sprite::color_format
		>,
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::texture_coordinates::automatic,
			sge::sprite::config::texture_ownership::shared
		>,
		libftl::sprite::detail::depth_element
	>
>
choices;

}
}

#endif
