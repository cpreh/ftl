#ifndef LIBFTL_BLUEPRINTS_LOAD_HPP_INCLUDED
#define LIBFTL_BLUEPRINTS_LOAD_HPP_INCLUDED

#include <libftl/archive/base_fwd.hpp>
#include <libftl/blueprints/data.hpp>
#include <libftl/blueprints/error.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/either/object_impl.hpp>

namespace libftl::blueprints
{
[[nodiscard]] LIBFTL_DETAIL_SYMBOL
    fcppt::either::object<libftl::blueprints::error, libftl::blueprints::data>
    load(libftl::archive::base const &);
}

#endif
