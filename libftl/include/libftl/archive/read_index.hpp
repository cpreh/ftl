#ifndef LIBFTL_ARCHIVE_READ_INDEX_HPP_INCLUDED
#define LIBFTL_ARCHIVE_READ_INDEX_HPP_INCLUDED

#include <libftl/archive/index.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace archive
{

LIBFTL_DETAIL_SYMBOL
fcppt::either::object<
	fcppt::string,
	libftl::archive::index
>
read_index(
	std::istream &
);

}
}

#endif
