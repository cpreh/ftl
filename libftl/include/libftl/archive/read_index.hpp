#ifndef LIBFTL_ARCHIVE_READ_INDEX_HPP_INCLUDED
#define LIBFTL_ARCHIVE_READ_INDEX_HPP_INCLUDED

#include <libftl/archive/index_result.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace archive
{

LIBFTL_DETAIL_SYMBOL
libftl::archive::index_result
read_index(
	std::istream &
);

}
}

#endif
