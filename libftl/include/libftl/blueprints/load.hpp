#ifndef LIBFTL_BLUEPRINTS_LOAD_HPP_INCLUDED
#define LIBFTL_BLUEPRINTS_LOAD_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <libftl/blueprints/data.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/either/object_impl.hpp>

namespace libftl
{
namespace blueprints
{
LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
    libftl::error,
    libftl::blueprints::data>
load(libftl::archive::base & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}
}

#endif
