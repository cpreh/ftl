#include <libftl/room/state.hpp>
#include <libftl/ship/state.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

libftl::ship::state::state(std::vector<libftl::room::state> &&_rooms) : rooms_{std::move(_rooms)} {}
