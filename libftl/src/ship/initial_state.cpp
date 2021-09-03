#include <libftl/error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/room/system.hpp>
#include <libftl/room/type.hpp>
#include <libftl/ship/initial_state.hpp>
#include <libftl/ship/state.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/room.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <libftl/xml/blueprints/ship_system_list.hpp>
#include <libftl/xml/blueprints/system_element.hpp>
#include <libftl/xml/labels/battery.hpp>
#include <libftl/xml/labels/cloaking.hpp>
#include <libftl/xml/labels/doors.hpp>
#include <libftl/xml/labels/drones.hpp>
#include <libftl/xml/labels/engines.hpp>
#include <libftl/xml/labels/hacking.hpp>
#include <libftl/xml/labels/img.hpp>
#include <libftl/xml/labels/max.hpp>
#include <libftl/xml/labels/medbay.hpp>
#include <libftl/xml/labels/mind.hpp>
#include <libftl/xml/labels/oxygen.hpp>
#include <libftl/xml/labels/pilot.hpp>
#include <libftl/xml/labels/power.hpp>
#include <libftl/xml/labels/room.hpp>
#include <libftl/xml/labels/sensors.hpp>
#include <libftl/xml/labels/shields.hpp>
#include <libftl/xml/labels/start.hpp>
#include <libftl/xml/labels/system_list.hpp>
#include <libftl/xml/labels/teleporter.hpp>
#include <libftl/xml/labels/weapons.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/either/error.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
fcppt::either::object<libftl::error, fcppt::optional::object<libftl::room::system>> load_system(
    libftl::sprite::images const &_images,
    fcppt::optional::object<libftl::xml::blueprints::system_element> const &_room,
    libftl::room::type const _room_type)
{
  return fcppt::optional::maybe(
      _room,
      []
      {
        return fcppt::either::make_success<libftl::error>(
            fcppt::optional::object<libftl::room::system>{});
      },
      [&_images,
       _room_type](libftl::xml::blueprints::system_element const &_system)
      {
        return fcppt::either::map(
            fcppt::optional::maybe(
                _system.attributes_.get<libftl::xml::labels::img>(),
                []
                {
                  return fcppt::either::make_success<libftl::error>(
                      fcppt::optional::object<sge::texture::const_part_shared_ptr>{});
                },
                [&_images](std::string const &_name)
                {
                  return fcppt::either::map(
                      _images.load(
                          libftl::archive::path{"ship"} / "interior" / (_name + ".png")),
                      [](sge::texture::const_part_shared_ptr const &_texture)
                      { return fcppt::optional::make(_texture); });
                }),
            [&_system, _room_type](
                fcppt::optional::object<sge::texture::const_part_shared_ptr> const &_texture)
            {
              return fcppt::optional::make(libftl::room::system{
                  _room_type,
                  _texture,
                  libftl::room::system::power{_system.attributes_.get<libftl::xml::labels::power>()},
                  fcppt::optional::map(
                      _system.attributes_.get<libftl::xml::labels::max>(),
                      [](unsigned const _max)
                      { return libftl::room::system::max_power{_max}; }),
                  libftl::ship::layout::room_id{_system.attributes_.get<libftl::xml::labels::room>()},
                  fcppt::optional::map(
                      _system.attributes_.get<libftl::xml::labels::start>(),
                      [](bool const _start)
                      { return libftl::room::system::available{_start}; })});
            });
      });
}

fcppt::either::object<libftl::error, std::vector<libftl::room::system>> load_all_systems(
    libftl::xml::blueprints::ship_system_list const &_systems,
    libftl::sprite::images const &_images)
{
 // TODO(philipp) turn this macro into a function
#define LOAD_IMPL(name) load_system(_images, _systems.content_.get<libftl::xml::labels::name>(), libftl::room::type::name)

  return fcppt::either::map(
      fcppt::either::sequence<fcppt::either::object<
          libftl::error,
          std::vector<fcppt::optional::object<libftl::room::system>>>>(
          std::vector<
              fcppt::either::object<libftl::error, fcppt::optional::object<libftl::room::system>>>{
              LOAD_IMPL(pilot),
              LOAD_IMPL(sensors),
              LOAD_IMPL(doors),
              LOAD_IMPL(shields),
              LOAD_IMPL(engines),
              LOAD_IMPL(medbay),
              LOAD_IMPL(clonebay),
              LOAD_IMPL(oxygen),
              LOAD_IMPL(teleporter),
              LOAD_IMPL(mind),
              LOAD_IMPL(hacking),
              LOAD_IMPL(drones),
              LOAD_IMPL(weapons),
              LOAD_IMPL(battery),
              LOAD_IMPL(cloaking) //,
              //LOAD_IMPL(artillery) TODO
          }),
      [](std::vector<fcppt::optional::object<libftl::room::system>> &&_result)
      { return fcppt::optional::cat<std::vector<libftl::room::system>>(std::move(_result)); });
}

libftl::room::state make_room_state(
    std::vector<libftl::room::system> const &_systems, libftl::ship::layout::room const &_room)
{
  return libftl::room::state{
      fcppt::optional::map(
          fcppt::algorithm::find_if_opt(
              _systems,
              [&_room](libftl::room::system const &_system)
              {
                return _system.room_ == _room.id_ &&
                       fcppt::optional::maybe(
                           _system.available_,
                           fcppt::const_(true),
                           [](libftl::room::system::available const _has_room)
                           { return _has_room.get(); });
              }),
          [](auto const _iterator) { return *_iterator; }),
      _room};
}
}

fcppt::either::object<libftl::error, libftl::ship::state> libftl::ship::initial_state(
    libftl::xml::blueprints::ship const &_blueprint,
    libftl::ship::layout::object const &_layout,
    libftl::sprite::images const &_images)
{
  return fcppt::either::map(
      load_all_systems(_blueprint.content_.get<libftl::xml::labels::system_list>(), _images),
      [&_layout](std::vector<libftl::room::system> const &_systems)
      {
        return libftl::ship::state{fcppt::algorithm::map<std::vector<libftl::room::state>>(
            _layout.rooms_,
            [&_systems](libftl::ship::layout::room const &_room)
            { return make_room_state(_systems, _room); })};
      });
}
