#include <libftl/blueprints/data.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::blueprints::data::data(
    normal_blueprints &&_normal_blueprints,
    dlc_blueprints &&_dlc_blueprints,
    dlc_blueprints_overwrites &&_dlc_blueprints_overwrites)
    : normal_blueprints_{std::move(_normal_blueprints)},
      dlc_blueprints_{std::move(_dlc_blueprints)},
      dlc_blueprints_overwrites_{std::move(_dlc_blueprints_overwrites)}
{
}

libftl::blueprints::data::data(data &&) noexcept = default;

libftl::blueprints::data &libftl::blueprints::data::operator=(data &&) noexcept = default;

libftl::blueprints::data::~data() = default;
