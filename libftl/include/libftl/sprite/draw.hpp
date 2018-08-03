#ifndef LIBFTL_SPRITE_DRAW_HPP_INCLUDED
#define LIBFTL_SPRITE_DRAW_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/sprite/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace sprite
{

LIBFTL_DETAIL_SYMBOL
void
draw(
	sge::renderer::device::ffp &,
	sge::renderer::context::ffp &,
	std::vector<
		libftl::sprite::object
	> const &
);

}
}

#endif
