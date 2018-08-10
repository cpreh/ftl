#include <libftl/ship/draw.hpp>
#include <libftl/ship/resources.hpp>
#include <libftl/sprite/color_format.hpp>
#include <libftl/sprite/object.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


std::vector<
	libftl::sprite::object
>
libftl::ship::draw(
	libftl::ship::resources const &_resources
)
{
	// TODO
	return
		std::vector<libftl::sprite::object>
		{
			libftl::sprite::object{
				sge::sprite::roles::pos{} =
					fcppt::math::vector::null<
						libftl::sprite::object::vector
					>(),
			sge::sprite::roles::texture0{} =
				libftl::sprite::object::texture_type{
					_resources.images_.base_.get()
				},
			sge::sprite::roles::color{} =
				sge::image::color::convert<
					libftl::sprite::color_format
				>(
					sge::image::color::predef::white()
				)
			}
		};
}
