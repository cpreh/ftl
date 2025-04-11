#include <libftl/archive/base_fwd.hpp>
#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/blueprints/find_ship.hpp>
#include <libftl/ship/load.hpp>
#include <libftl/ship/load_error.hpp>
#include <libftl/ship/resources.hpp>
#include <libftl/ship/images/error.hpp>
#include <libftl/ship/images/load.hpp>
#include <libftl/ship/images/name.hpp>
#include <libftl/ship/images/object.hpp>
#include <libftl/ship/layout/load.hpp>
#include <libftl/ship/layout/load_error.hpp>
#include <libftl/ship/layout/load_xml.hpp>
#include <libftl/ship/layout/load_xml_error.hpp>
#include <libftl/ship/layout/name.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/layout.hpp>
#include <libftl/xml/ship/result.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::ship::load_error, libftl::ship::resources> libftl::ship::load(
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
            return libftl::ship::load_error{
                .name_ = _name,
                .value_ = libftl::ship::load_error::variant{libftl::ship::load_error::not_found{}}};
          }),
      [&_archive, &_images, &_name](
          fcppt::reference<libftl::xml::blueprints::ship const> const _blueprint)
      {
        libftl::ship::layout::name const layout_name{
            _blueprint->attributes_.get<libftl::xml::labels::layout>()};

        return fcppt::either::bind(
            fcppt::either::map_failure(
                libftl::ship::layout::load_xml(_archive, layout_name),
                [&_name](libftl::ship::layout::load_xml_error &&_error)
                {
                  return libftl::ship::load_error{
                      .name_ = _name,
                      .value_ = libftl::ship::load_error::variant{std::move(_error)}};
                }),
            [&_archive, &_blueprint, &_images, &layout_name, &_name](
                libftl::xml::ship::result &&_ship)
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
                  fcppt::either::map_failure(
                      libftl::ship::images::load(
                          _images, _blueprint.get(), fcppt::make_cref(_ship), image_name),
                      [&_name](libftl::ship::images::error &&_error)
                      {
                        return libftl::ship::load_error{
                            .name_ = _name,
                            .value_ = libftl::ship::load_error::variant{std::move(_error)}};
                      }),
                  fcppt::either::map_failure(
                      libftl::ship::layout::load(_archive, layout_name),
                      [&_name](libftl::ship::layout::load_error &&_error)
                      {
                        return libftl::ship::load_error{
                            .name_ = _name,
                            .value_ = libftl::ship::load_error::variant{std::move(_error)}};
                      }));
            });
      });
}
