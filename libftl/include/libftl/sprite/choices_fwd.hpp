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
#include <fcppt/mpl/list/object.hpp>

namespace libftl::sprite
{
using choices = sge::sprite::config::choices<
    libftl::sprite::type_choices,
    sge::sprite::config::pos<sge::sprite::config::pos_option::pos>,
    sge::sprite::config::normal_size<sge::sprite::config::texture_size_option::maybe>,
    fcppt::mpl::list::object<
        sge::sprite::config::with_color<libftl::sprite::color_format>,
        sge::sprite::config::with_texture<
            sge::sprite::config::texture_level_count<1U>,
            sge::sprite::config::texture_coordinates::automatic,
            sge::sprite::config::texture_ownership::shared>,
        libftl::sprite::detail::depth_element>>;

}

#endif
