#include <libftl/error.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/blueprints/find_ship.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/ship/load.hpp>
#include <libftl/ship/resources.hpp>
#include <libftl/ship/images/load.hpp>
#include <libftl/ship/images/name.hpp>
#include <libftl/ship/layout/load.hpp>
#include <libftl/ship/layout/load_xml.hpp>
#include <libftl/ship/layout/name.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/layout.hpp>
#include <libftl/xml/ship/result.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, libftl::ship::resources> libftl::ship::load(
    libftl::archive::base const &_archive,
    fcppt::reference<libftl::blueprints::data const> const _blueprints,
    libftl::sprite::images const &_images,
    std::string const &_name)
{
  return fcppt::either::bind(
      fcppt::either::from_optional(
          libftl::blueprints::find_ship(_blueprints, _name),
          [&_name]
          {
            return libftl::error{
                FCPPT_TEXT("Ship \"") + fcppt::from_std_string(_name) +
                FCPPT_TEXT("\" not found in any blueprint file.")};
          }),
      [&_archive, &_images](fcppt::reference<libftl::xml::blueprints::ship const> const _blueprint)
      {
        libftl::ship::layout::name const layout_name{
            _blueprint->attributes_.get<libftl::xml::labels::layout>()};

        return fcppt::either::bind(
            libftl::ship::layout::load_xml(_archive, layout_name),
            [&_archive, &_blueprint, &_images, &layout_name](libftl::xml::ship::result &&_ship)
            {
              libftl::ship::images::name const image_name{
                  _blueprint->attributes_.get<libftl::xml::labels::img>()};

              return fcppt::either::apply(
                  [&_ship](
                      libftl::ship::images::object &&_ship_images,
                      libftl::ship::layout::object &&_layout)
                  {
                    return libftl::ship::resources{
                        std::move(_ship), std::move(_ship_images), std::move(_layout)};
                  },
                  libftl::ship::images::load(
                      _images, _blueprint.get(), fcppt::make_cref(_ship), image_name),
                  libftl::ship::layout::load(_archive, layout_name));
            });
      });
}
