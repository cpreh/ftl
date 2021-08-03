#include <libftl/room/system.hpp>
#include <libftl/room/type.hpp>
#include <libftl/ship/layout/room_id.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::room::system::system(
    libftl::room::type const _type,
    fcppt::optional::object<sge::texture::const_part_shared_ptr> _background,
    power const _power,
    fcppt::optional::object<max_power> const _max_power,
    libftl::ship::layout::room_id const _room,
    fcppt::optional::object<available> const _available)
    : type_{_type},
      background_{std::move(_background)},
      power_{_power},
      max_power_{_max_power},
      room_{_room},
      available_{_available}
{
}
