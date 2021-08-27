#include <libftl/error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/ship/images/load.hpp>
#include <libftl/ship/images/name.hpp>
#include <libftl/ship/images/object.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <libftl/xml/labels/cloak.hpp>
#include <libftl/xml/labels/explosion.hpp>
#include <libftl/xml/labels/floor.hpp>
#include <libftl/xml/labels/gib1.hpp>
#include <libftl/xml/labels/gib2.hpp>
#include <libftl/xml/labels/gib3.hpp>
#include <libftl/xml/labels/gib4.hpp>
#include <libftl/xml/labels/gib5.hpp>
#include <libftl/xml/labels/gib6.hpp>
#include <libftl/xml/labels/offsets.hpp>
#include <libftl/xml/ship/explosion.hpp>
#include <libftl/xml/ship/gib.hpp>
#include <libftl/xml/ship/offset.hpp>
#include <libftl/xml/ship/offsets.hpp>
#include <libftl/xml/ship/result.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{
fcppt::either::object<libftl::error, sge::texture::const_part_shared_ptr>
find_image(libftl::sprite::images const &_images, std::string const &_file_name)
{
  return fcppt::either::match(
      _images.load(libftl::archive::path{"ship"} / std::string{_file_name}),
      [&_file_name, &_images](libftl::error &&_error1)
      {
        return fcppt::either::map_failure(
            _images.load(libftl::archive::path{"ships_noglow"} / std::string{_file_name}),
            [&_error1](libftl::error &&_error2) {
              return libftl::error{
                  std::move(_error1.get()) + FCPPT_TEXT("\n") + std::move(_error2.get())};
            });
      },
      [](sge::texture::const_part_shared_ptr &&_texture)
      { return fcppt::either::make_success<libftl::error>(std::move(_texture)); });
}

fcppt::either::object<libftl::error, libftl::ship::images::object::base>
load_base(libftl::sprite::images const &_images, libftl::ship::images::name const &_ship_name)
{
  return fcppt::either::map(
      find_image(_images, _ship_name.get() + "_base.png"),
      [](sge::texture::const_part_shared_ptr &&_texture)
      { return libftl::ship::images::object::base{std::move(_texture)}; });
}

fcppt::either::object<libftl::error, fcppt::optional::object<libftl::ship::images::object::shield>>
load_shield(
    libftl::sprite::images const &_images,
    libftl::xml::generated::blueprints::ship_blueprint const &_blueprint)
{
  return fcppt::optional::maybe(
      fcppt::container::maybe_front(_blueprint.shieldImage()),
      []
      {
        return fcppt::either::make_success<libftl::error>(
            fcppt::optional::object<libftl::ship::images::object::shield>{});
      },
      [&_images](fcppt::reference<xml_schema::string const> const _shield)
      {
        return fcppt::either::map(
            find_image(_images, std::string{_shield.get() + "_shields1.png"}),
            [](sge::texture::const_part_shared_ptr &&_texture) {
              return fcppt::optional::make(
                  libftl::ship::images::object::shield{std::move(_texture)});
            });
      });
}

using get_offset_function =
    fcppt::function<fcppt::optional::object<libftl::xml::ship::offset> const &(
        libftl::xml::ship::offsets const &)>;

template <typename Type>
fcppt::either::object<libftl::error, fcppt::optional::object<Type>> load_offset_image(
    libftl::sprite::images const &_images,
    fcppt::reference<libftl::xml::ship::result const> const _ship,
    get_offset_function const &_get_offset,
    std::string const &_name)
{
  auto const image_from_offset(
      [&_images, &_name](libftl::xml::ship::offset const &_offset)
      {
        return fcppt::either::map(
            find_image(_images, _name),
            [&_offset](sge::texture::const_part_shared_ptr &&_texture)
            {
              return fcppt::optional::make(Type{
                  libftl::ship::images::object::offset_image{_offset, std::move(_texture)}});
            });
      });

  return fcppt::optional::maybe(
      fcppt::optional::bind(
          fcppt::record::get<libftl::xml::labels::offsets>(_ship.get()),
          [&_get_offset](libftl::xml::ship::offsets const &_offsets)
          { return _get_offset(_offsets); }),
      [] { return fcppt::either::make_success<libftl::error>(fcppt::optional::object<Type>{}); },
      image_from_offset);
}

fcppt::either::object<libftl::error, libftl::ship::images::object::gib_image> load_mandatory_gib(
    libftl::sprite::images const &_images,
    libftl::xml::ship::gib const &_gib,
    libftl::ship::images::name const &_ship_name,
    unsigned const _number)
{
  return fcppt::either::map(
      find_image(
          _images, _ship_name.get() + "_gib" + fcppt::output_to_std_string(_number) + ".png"),
      [&_gib](sge::texture::const_part_shared_ptr &&_texture)
      { return libftl::ship::images::object::gib_image{_gib, std::move(_texture)}; });
}

fcppt::either::
    object<libftl::error, fcppt::optional::object<libftl::ship::images::object::gib_image>>
    load_optional_gib(
        libftl::sprite::images const &_images,
        fcppt::optional::object<libftl::xml::ship::gib> const &_opt_gib,
        libftl::ship::images::name const &_ship_name,
        unsigned const _number)
{
  return fcppt::optional::maybe(
      _opt_gib,
      []
      {
        return fcppt::either::make_success<libftl::error>(
            fcppt::optional::object<libftl::ship::images::object::gib_image>{});
      },
      [&_images, &_ship_name, &_number](libftl::xml::ship::gib const &_gib)
      {
        return fcppt::either::map(
            load_mandatory_gib(_images, _gib, _ship_name, _number),
            [](libftl::ship::images::object::gib_image &&_gib_image)
            { return fcppt::optional::make(_gib_image); });
      });
}

fcppt::either::object<libftl::error, std::vector<libftl::ship::images::object::gib_image>>
load_gibs(
    libftl::sprite::images const &_images,
    fcppt::reference<libftl::xml::ship::explosion const> const _explosion,
    libftl::ship::images::name const &_ship_name)
{
  auto const load_mandatory_impl(
      [&_ship_name, &_images](libftl::xml::ship::gib const &_gib, unsigned const _number)
      { return load_mandatory_gib(_images, _gib, _ship_name, _number); });

  auto const load_optional_impl(
      [&_ship_name, &_images](
          fcppt::optional::object<libftl::xml::ship::gib> const &_gib, unsigned const _number)
      { return load_optional_gib(_images, _gib, _ship_name, _number); });

  return fcppt::either::apply(
      [](libftl::ship::images::object::gib_image &&_gib1,
         libftl::ship::images::object::gib_image &&_gib2,
         libftl::ship::images::object::gib_image &&_gib3,
         libftl::ship::images::object::gib_image &&_gib4,
         fcppt::optional::object<libftl::ship::images::object::gib_image> &&_gib5,
         fcppt::optional::object<libftl::ship::images::object::gib_image> &&_gib6)
      {
        return fcppt::container::join(
            std::vector<libftl::ship::images::object::gib_image>{
                std::move(_gib1), std::move(_gib2), std::move(_gib3), std::move(_gib4)},
            fcppt::optional::to_container<std::vector<libftl::ship::images::object::gib_image>>(
                std::move(_gib5)),
            fcppt::optional::to_container<std::vector<libftl::ship::images::object::gib_image>>(
                std::move(_gib6)));
      },
      load_mandatory_impl(fcppt::record::get<libftl::xml::labels::gib1>(_explosion->content_), 1U),
      load_mandatory_impl(fcppt::record::get<libftl::xml::labels::gib2>(_explosion->content_), 2U),
      load_mandatory_impl(fcppt::record::get<libftl::xml::labels::gib3>(_explosion->content_), 3U),
      load_mandatory_impl(fcppt::record::get<libftl::xml::labels::gib4>(_explosion->content_), 4U),
      load_optional_impl(
          fcppt::record::get<libftl::xml::labels::gib5>(_explosion->content_),
          5U), // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      load_optional_impl(
          fcppt::record::get<libftl::xml::labels::gib6>(_explosion->content_),
          6U) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  );
}

}

fcppt::either::object<libftl::error, libftl::ship::images::object> libftl::ship::images::load(
    libftl::sprite::images const &_images,
    libftl::xml::generated::blueprints::ship_blueprint const &_blueprint,
    fcppt::reference<libftl::xml::ship::result const> const _ship,
    libftl::ship::images::name const &_ship_name)
{
  return fcppt::either::apply(
      [](libftl::ship::images::object::base &&_base,
         fcppt::optional::object<libftl::ship::images::object::shield> &&_shield,
         fcppt::optional::object<libftl::ship::images::object::floor> &&_floor,
         fcppt::optional::object<libftl::ship::images::object::cloak> &&_cloak,
         std::vector<libftl::ship::images::object::gib_image> &&_gibs)
      {
        return libftl::ship::images::object{
            std::move(_base),
            std::move(_shield),
            std::move(_floor),
            std::move(_cloak),
            std::move(_gibs)};
      },
      load_base(_images, _ship_name),
      load_shield(_images, _blueprint),
      load_offset_image<libftl::ship::images::object::floor>(
          _images,
          _ship,
          get_offset_function{
              [](libftl::xml::ship::offsets const &_offsets)
                  -> fcppt::optional::object<libftl::xml::ship::offset> const & {
                return fcppt::record::get<libftl::xml::labels::floor>(_offsets.content_);
              }},
          _ship_name.get() + "_floor.png"),
      load_offset_image<libftl::ship::images::object::cloak>(
          _images,
          _ship,
          get_offset_function{
              [](libftl::xml::ship::offsets const &_offsets)
                  -> fcppt::optional::object<libftl::xml::ship::offset> const & {
                return fcppt::record::get<libftl::xml::labels::cloak>(_offsets.content_);
              }},
          fcppt::optional::from(
              fcppt::optional::map(
                  fcppt::container::maybe_front(_blueprint.cloakImage()),
                  [](fcppt::reference<xml_schema::string const> const _cloak)
                  { return std::string{_cloak.get()}; }),
              [&_ship_name] { return _ship_name.get(); }) +
              "_cloak.png"),
      load_gibs(
          _images,
          fcppt::make_cref(fcppt::record::get<libftl::xml::labels::explosion>(_ship.get())),
          _ship_name));
}
