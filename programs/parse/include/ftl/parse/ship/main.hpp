#ifndef FTL_PARSE_SHIP_MAIN_HPP_INCLUDED
#define FTL_PARSE_SHIP_MAIN_HPP_INCLUDED

#include <ftl/parse/error.hpp>
#include <ftl/parse/ship/arguments_fwd.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <fcppt/either/error.hpp>

namespace ftl::parse::ship
{
[[nodiscard]] fcppt::either::error<ftl::parse::error>
main(libftl::archive::base const &, ftl::parse::ship::arguments const &);
}

#endif
