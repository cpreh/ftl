#ifndef LIBFTL_BLUEPRINTS_FIND_SHIP_HPP_INCLUDED
#define LIBFTL_BLUEPRINTS_FIND_SHIP_HPP_INCLUDED

#include <libftl/blueprints/data_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/optional/reference.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

namespace libftl::blueprints
{
[[nodiscard]]
LIBFTL_DETAIL_SYMBOL
fcppt::optional::reference<libftl::xml::blueprints::ship const>
find_ship(fcppt::reference<libftl::blueprints::data const>, std::string_view);

}

#endif
