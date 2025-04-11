#ifndef LIBFTL_ARCHIVE_READ_INDEX_HPP_INCLUDED
#define LIBFTL_ARCHIVE_READ_INDEX_HPP_INCLUDED

#include <libftl/archive/index.hpp>
#include <libftl/archive/index_error.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::archive
{
LIBFTL_DETAIL_SYMBOL
fcppt::either::object<libftl::archive::index_error, libftl::archive::index> read_index(std::istream &);

}

#endif
