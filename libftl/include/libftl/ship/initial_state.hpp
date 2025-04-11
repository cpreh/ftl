#ifndef LIBFTL_SHIP_INITIAL_STATE_HPP_INCLUDED
#define LIBFTL_SHIP_INITIAL_STATE_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/state.hpp>
#include <libftl/ship/layout/object_fwd.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <libftl/sprite/load_error.hpp>
#include <libftl/xml/blueprints/ship.hpp>
#include <fcppt/either/object_impl.hpp>

namespace libftl::ship
{
[[nodiscard]] LIBFTL_DETAIL_SYMBOL
    fcppt::either::object<libftl::sprite::load_error, libftl::ship::state>
    initial_state(
        libftl::xml::blueprints::ship const &,
        libftl::ship::layout::object const &,
        libftl::sprite::images const &);
}

#endif
