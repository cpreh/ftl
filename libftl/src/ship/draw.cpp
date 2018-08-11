#include <libftl/ship/draw.hpp>
#include <libftl/ship/resources.hpp>
#include <libftl/sprite/color_format.hpp>
#include <libftl/sprite/depth.hpp>
#include <libftl/sprite/depth_role.hpp>
#include <libftl/sprite/object.hpp>
#include <libftl/sprite/size_or_texture_size.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/texture_size.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

libftl::sprite::object
base_image(
	libftl::ship::resources const &_resources
)
{
	return
		libftl::sprite::object{
			sge::sprite::roles::pos{} =
				fcppt::math::vector::null<
					libftl::sprite::object::vector
				>(),
			sge::sprite::roles::size_or_texture_size{} =
				libftl::sprite::size_or_texture_size{
					libftl::sprite::object::dim{
						fcppt::cast::size<
							libftl::sprite::object::unit
						>(
							_resources.ship_root_->img().w()
						),
						fcppt::cast::size<
							libftl::sprite::object::unit
						>(
							_resources.ship_root_->img().h()
						)
					}
				},
			sge::sprite::roles::texture0{} =
				libftl::sprite::object::texture_type{
					_resources.images_.base_.get()
				},
			sge::sprite::roles::color{} =
				sge::image::color::convert<
					libftl::sprite::color_format
				>(
					sge::image::color::predef::white()
				),
			libftl::sprite::depth_role{} =
				libftl::sprite::depth::base
		};
}

fcppt::optional::object<
	libftl::sprite::object
>
floor_image(
	libftl::ship::resources const &_resources
)
{
	return
		fcppt::optional::map(
			_resources.images_.floor_,
			[](libftl::ship::images::object::floor const &_floor)
			{
				return
					libftl::sprite::object{
						sge::sprite::roles::pos{} =
							libftl::sprite::object::vector{
								fcppt::cast::size<
									libftl::sprite::object::unit
								>(
									_floor.get().offset_.x()
								),
								fcppt::cast::size<
									libftl::sprite::object::unit
								>(
									_floor.get().offset_.y()
								)
							},
						sge::sprite::roles::size_or_texture_size{} =
							// TODO?
							libftl::sprite::size_or_texture_size{
								sge::sprite::types::texture_size{}
							},
						sge::sprite::roles::texture0{} =
							libftl::sprite::object::texture_type{
								_floor.get().image_
							},
						sge::sprite::roles::color{} =
							sge::image::color::convert<
								libftl::sprite::color_format
							>(
								sge::image::color::predef::white()
							),
						libftl::sprite::depth_role{} =
							libftl::sprite::depth::floor
					};
			}
		);
}

}

std::vector<
	libftl::sprite::object
>
libftl::ship::draw(
	libftl::ship::resources const &_resources
)
{
	return
		fcppt::algorithm::join(
			std::vector<libftl::sprite::object>{
				base_image(_resources)
			},
			fcppt::optional::to_container<
				std::vector<libftl::sprite::object>
			>(
				floor_image(_resources)
			)
		);
}
