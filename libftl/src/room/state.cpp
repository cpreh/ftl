#include <libftl/room/state.hpp>
#include <libftl/room/system.hpp>
#include <libftl/ship/layout/room.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::room::state::state(
    fcppt::optional::object<libftl::room::system> &&_system,
    libftl::ship::layout::room const _layout)
    : system_{std::move(_system)}, layout_{_layout}
{
}
