#ifndef LIBFTL_ARCHIVE_EXTRACT_HPP_INCLUDED
#define LIBFTL_ARCHIVE_EXTRACT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/archive/entry_fwd.hpp>
#include <fcppt/io/optional_buffer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace archive
{

LIBFTL_DETAIL_SYMBOL
fcppt::io::optional_buffer
extract(
	std::istream &,
	libftl::archive::entry const &
);

}
}

#endif
