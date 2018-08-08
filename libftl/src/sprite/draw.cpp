#include <libftl/sprite/choices.hpp>
#include <libftl/sprite/draw.hpp>
#include <libftl/sprite/object.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/all.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


void
libftl::sprite::draw(
	sge::renderer::device::ffp &_renderer_device,
	sge::renderer::context::ffp &_renderer_context,
	std::vector<
		libftl::sprite::object
	> const &_sprites
)
{
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			libftl::sprite::choices
		>
	>
	sprite_buffers{
		_renderer_device,
		sge::sprite::buffers::option::static_
	};

	typedef
	sge::sprite::state::all_choices
	state_choices;

	sge::sprite::state::object<
		state_choices
	>
	sprite_states{
		_renderer_device,
		sge::sprite::state::parameters<
			state_choices
		>{}
	};

	sge::sprite::process::all(
		_renderer_context,
		sge::sprite::geometry::make_random_access_range(
			_sprites
		),
		sprite_buffers,
		sge::sprite::compare::nothing{},
		sprite_states
	);
}