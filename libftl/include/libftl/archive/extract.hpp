#ifndef LIBFTL_ARCHIVE_EXTRACT_HPP_INCLUDED
#define LIBFTL_ARCHIVE_EXTRACT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/archive/file_fwd.hpp>
#include <fcppt/io/optional_buffer.hpp>


namespace libftl
{
namespace archive
{

LIBFTL_DETAIL_SYMBOL
fcppt::io::optional_buffer
extract(
	libftl::archive::file const &
);

}
}

#endif
