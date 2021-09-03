#ifndef LIBFTL_XML_SECTORS_LOAD_HPP_INCLUDED
#define LIBFTL_XML_SECTORS_LOAD_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/generated/sectors.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::sectors
{
[[nodiscard]]
LIBFTL_DETAIL_SYMBOL
fcppt::either::
    object<libftl::error, fcppt::unique_ptr<libftl::xml::generated::sectors::sectors_root>>
    load(std::istream &);
}

#endif
