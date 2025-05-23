#ifndef LIBFTL_OPTIONS_OPEN_ARCHIVE_HPP_INCLUDED
#define LIBFTL_OPTIONS_OPEN_ARCHIVE_HPP_INCLUDED

#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/open_error.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/options/resource_variant_fwd.hpp>
#include <fcppt/either/object_impl.hpp>

namespace libftl::options
{
LIBFTL_DETAIL_SYMBOL
fcppt::either::object<libftl::archive::open_error, libftl::archive::base_unique_ptr>
open_archive(libftl::options::resource_variant const &);

}

#endif
