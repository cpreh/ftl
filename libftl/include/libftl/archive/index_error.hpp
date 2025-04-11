#ifndef LIBFTL_ARCHIVE_INDEX_ERROR_HPP_INCLUDED
#define LIBFTL_ARCHIVE_INDEX_ERROR_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace libftl::archive
{
// TODO(philipp): Change alda::raw::stream::error type.
FCPPT_DECLARE_STRONG_TYPEDEF(fcppt::string, index_error);
}

#endif
