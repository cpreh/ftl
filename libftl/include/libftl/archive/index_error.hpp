#ifndef LIBFTL_ARCHIVE_INDEX_ERROR_HPP_INCLUDED
#define LIBFTL_ARCHIVE_INDEX_ERROR_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <alda/raw/stream/error.hpp>
#include <fcppt/io/ostream_fwd.hpp>

namespace libftl::archive
{
struct index_error
{
  alda::raw::stream::error value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::archive::index_error const &);
}

#endif
