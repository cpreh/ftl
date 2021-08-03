#ifndef LIBFTL_ARCHIVE_ENTRY_OUTPUT_HPP_INCLUDED
#define LIBFTL_ARCHIVE_ENTRY_OUTPUT_HPP_INCLUDED

#include <libftl/archive/entry_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/io/ostream_fwd.hpp>

namespace libftl
{
namespace archive
{
LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::archive::entry const &);

}
}

#endif
