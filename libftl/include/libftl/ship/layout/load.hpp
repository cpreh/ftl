#ifndef LIBFTL_SHIP_LAYOUT_LOAD_HPP_INCLUDED
#define LIBFTL_SHIP_LAYOUT_LOAD_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/ship/layout/name_fwd.hpp>
#include <libftl/ship/layout/object.hpp>
#include <fcppt/either/object_impl.hpp>

namespace libftl::ship::layout
{
[[nodiscard]] LIBFTL_DETAIL_SYMBOL
    fcppt::either::object<libftl::error, libftl::ship::layout::object>
    load(libftl::archive::base const &, libftl::ship::layout::name const &);
}

#endif
