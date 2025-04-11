#ifndef LIBFTL_XML_SHIP_LOAD_HPP_INCLUDED
#define LIBFTL_XML_SHIP_LOAD_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/xml/ship/result.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::ship
{
[[nodiscard]] LIBFTL_DETAIL_SYMBOL
    fcppt::either::object<libftl::xml::error, libftl::xml::ship::result>
    load(std::istream &);
}

#endif
