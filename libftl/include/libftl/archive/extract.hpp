#ifndef LIBFTL_ARCHIVE_EXTRACT_HPP_INCLUDED
#define LIBFTL_ARCHIVE_EXTRACT_HPP_INCLUDED

#include <libftl/archive/file_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/io/optional_buffer.hpp>

namespace libftl::archive
{
LIBFTL_DETAIL_SYMBOL
fcppt::io::optional_buffer extract(libftl::archive::file const &);

}

#endif
