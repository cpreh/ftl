#include <libftl/error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/impl/xsd/require_one.hpp>
#include <libftl/impl/xsd/to_fcppt_optional.hpp>
#include <libftl/room/system.hpp>
#include <libftl/room/type.hpp>
#include <libftl/ship/initial_state.hpp>
#include <libftl/ship/state.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/room.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/const.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/either/error.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/monad.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/either/sequence.hpp>
#include <fcppt/monad/chain.hpp>
#include <fcppt/monad/return.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/tree/containers.hxx>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
fcppt::either::object<libftl::error, fcppt::optional::object<libftl::room::system>> load_system(
    libftl::sprite::images const &_images,
    ::xsd::cxx::tree::sequence<libftl::xml::generated::blueprints::system> const &_room_list,
    libftl::room::type const _room_type)
{
  return fcppt::optional::maybe(
      fcppt::container::maybe_front(_room_list),
      []
      {
        return fcppt::either::make_success<libftl::error>(
            fcppt::optional::object<libftl::room::system>{});
      },
      [&_images,
       _room_type](fcppt::reference<libftl::xml::generated::blueprints::system const> const _system)
      {
        return fcppt::either::map(
            fcppt::optional::maybe(
                libftl::impl::xsd::to_fcppt_optional(fcppt::make_cref(_system.get().img())),
                []
                {
                  return fcppt::either::make_success<libftl::error>(
                      fcppt::optional::object<sge::texture::const_part_shared_ptr>{});
                },
                [&_images](fcppt::reference<xml_schema::string const> const _name)
                {
                  return fcppt::either::map(
                      _images.load(
                          libftl::archive::path{"ship"} / "interior" / (_name.get() + ".png")),
                      [](sge::texture::const_part_shared_ptr const &_texture)
                      { return fcppt::optional::make(_texture); });
                }),
            [&_system, _room_type](
                fcppt::optional::object<sge::texture::const_part_shared_ptr> const &_texture)
            {
              return fcppt::optional::make(libftl::room::system{
                  _room_type,
                  _texture,
                  libftl::room::system::power{_system.get().power()},
                  fcppt::optional::map(
                      libftl::impl::xsd::to_fcppt_optional(fcppt::make_cref(_system.get().max())),
                      [](fcppt::reference<::xml_schema::unsigned_int const> const _max)
                      { return libftl::room::system::max_power{_max.get()}; }),
                  libftl::ship::layout::room_id{_system.get().room()},
                  fcppt::optional::map(
                      libftl::impl::xsd::to_fcppt_optional(fcppt::make_cref(_system.get().start())),
                      [](fcppt::reference<::xml_schema::boolean const> const _start)
                      { return libftl::room::system::available{_start.get()}; })});
            });
      });
}

fcppt::either::object<libftl::error, std::vector<libftl::room::system>> load_all_systems(
    libftl::xml::generated::blueprints::system_list const &_systems,
    libftl::sprite::images const &_images)
{
#define LOAD_IMPL(name) load_system(_images, _systems.name(), libftl::room::type::name)

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
    libftl::xml::generated::blueprints::ship_blueprint const &_blueprint,
    libftl::ship::layout::object const &_layout,
    libftl::sprite::images const &_images)
{
  return fcppt::monad::chain(
      libftl::impl::xsd::require_one(FCPPT_TEXT("systemList"), _blueprint.systemList()),
      [&_images](fcppt::reference<libftl::xml::generated::blueprints::system_list const> const
                     _system_list) { return load_all_systems(_system_list.get(), _images); },
      [&_layout](std::vector<libftl::room::system> const &_systems)
      {
        return fcppt::monad::return_<fcppt::either::error<libftl::error>>(
            libftl::ship::state{fcppt::algorithm::map<std::vector<libftl::room::state>>(
                _layout.rooms_,
                [&_systems](libftl::ship::layout::room const &_room)
                { return make_room_state(_systems, _room); })});
      });
}
