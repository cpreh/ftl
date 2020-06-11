#include <libftl/sprite/choices.hpp>
#include <libftl/sprite/depth.hpp>
#include <libftl/sprite/depth_role.hpp>
#include <libftl/sprite/draw.hpp>
#include <libftl/sprite/object.hpp>
#include <libftl/sprite/resolution.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/sprite/projection_dim.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/geometry/make_random_access_range.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/process/with_options.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/enum/array_impl.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
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
		fcppt::reference_to_base<
			sge::renderer::device::core
		>(
			fcppt::make_ref(
				_renderer_device
			)
		),
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

	typedef
	sge::sprite::process::options<
		sge::sprite::process::geometry_options::update
	>
	sprite_options;

	typedef
	fcppt::enum_::array<
		libftl::sprite::depth,
		std::vector<
			libftl::sprite::object
		>
	>
	sprite_depth_array;

	sprite_depth_array const sprite_levels{
		fcppt::algorithm::fold(
			_sprites,
			fcppt::enum_::array_init<
				sprite_depth_array
			>(
				[](libftl::sprite::depth)
				{
					return
						std::vector<libftl::sprite::object>{};
				}
			),
			[](libftl::sprite::object const &_sprite, sprite_depth_array &&_sprite_levels)
			{
				_sprite_levels[
					_sprite.get<
						libftl::sprite::depth_role
					>()
				].push_back(
					_sprite
				);

				return
					std::move(_sprite_levels);
			}
		)
	};

	for(
		libftl::sprite::depth const depth
		:
		fcppt::enum_::make_range<
			libftl::sprite::depth
		>()
	)
		sge::sprite::process::with_options<
			sprite_options
		>(
			_renderer_context,
			sge::sprite::geometry::make_random_access_range(
				sprite_levels[depth]
			),
			sprite_buffers,
			sge::sprite::compare::nothing{},
			sprite_states,
			sge::sprite::state::default_options<
				state_choices
			>().fixed_projection(
				sge::sprite::projection_dim{
					libftl::sprite::resolution()
				}
			)
		);
}
