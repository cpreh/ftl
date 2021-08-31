#include <libftl/impl/room/draw.hpp>
#include <libftl/ship/draw.hpp>
#include <libftl/ship/resources.hpp>
#include <libftl/sprite/depth.hpp>
#include <libftl/sprite/depth_role.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/sprite/object.hpp>
#include <libftl/sprite/size_or_texture_size.hpp>
#include <libftl/sprite/white.hpp>
#include <libftl/xml/labels/h.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/w.hpp>
#include <libftl/xml/labels/x.hpp>
#include <libftl/xml/labels/y.hpp>
#include <libftl/xml/ship/img.hpp>
#include <libftl/xml/ship/offset.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size_or_texture_size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/texture_size.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
libftl::sprite::object base_image(libftl::ship::resources const &_resources)
{
  libftl::xml::ship::img const &img{_resources.ship_.get<libftl::xml::labels::img>()};

  return libftl::sprite::object{
      sge::sprite::roles::pos{} = fcppt::math::vector::null<libftl::sprite::object::vector>(),
      sge::sprite::roles::size_or_texture_size{} =
          libftl::sprite::size_or_texture_size{libftl::sprite::object::dim{
              fcppt::cast::size<libftl::sprite::object::unit>(
                  fcppt::record::get<libftl::xml::labels::w>(img.attributes_)),
              fcppt::cast::size<libftl::sprite::object::unit>(
                  fcppt::record::get<libftl::xml::labels::h>(img.attributes_))}},
      sge::sprite::roles::texture0{} =
          libftl::sprite::object::texture_type{_resources.images_.base_.get()},
      sge::sprite::roles::color{} = libftl::sprite::white(),
      libftl::sprite::depth_role{} = libftl::sprite::depth::base};
}

fcppt::optional::object<libftl::sprite::object>
floor_image(libftl::ship::resources const &_resources)
{
  return fcppt::optional::map(
      _resources.images_.floor_,
      [](libftl::ship::images::object::floor const &_floor)
      {
        libftl::xml::ship::offset const &floor{_floor.get().offset_};

        return libftl::sprite::object{
            sge::sprite::roles::pos{} =
                libftl::sprite::object::vector{
                    fcppt::cast::size<libftl::sprite::object::unit>(
                        fcppt::record::get<libftl::xml::labels::x>(floor.attributes_)),
                    fcppt::cast::size<libftl::sprite::object::unit>(
                        fcppt::record::get<libftl::xml::labels::y>(floor.attributes_))},
            sge::sprite::roles::size_or_texture_size{} =
                libftl::sprite::size_or_texture_size{sge::sprite::types::texture_size{}},
            sge::sprite::roles::texture0{} =
                libftl::sprite::object::texture_type{_floor.get().image_},
            sge::sprite::roles::color{} = libftl::sprite::white(),
            libftl::sprite::depth_role{} = libftl::sprite::depth::floor};
      });
}

}

std::vector<libftl::sprite::object>
libftl::ship::draw(libftl::sprite::images const &_images, libftl::ship::resources const &_resources)
{
  return fcppt::container::join(
      std::vector<libftl::sprite::object>{base_image(_resources)},
      fcppt::optional::to_container<std::vector<libftl::sprite::object>>(floor_image(_resources)),
      libftl::impl::room::draw(_images, _resources.ship_, _resources.layout_));
}
