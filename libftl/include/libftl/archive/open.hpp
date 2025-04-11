#ifndef LIBFTL_ARCHIVE_OPEN_HPP_INCLUDED
#define LIBFTL_ARCHIVE_OPEN_HPP_INCLUDED

#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/open_error.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace libftl::archive
{
LIBFTL_DETAIL_SYMBOL
fcppt::either::object<libftl::archive::open_error, libftl::archive::base_unique_ptr>
open(std::filesystem::path &&);
}

#endif
