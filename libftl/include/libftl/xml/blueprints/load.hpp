#ifndef LIBFTL_XML_BLUEPRINTS_LOAD_HPP_INCLUDED
#define LIBFTL_XML_BLUEPRINTS_LOAD_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/xml/blueprints/result.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::blueprints
{
[[nodiscard]] LIBFTL_DETAIL_SYMBOL
    fcppt::either::object<libftl::xml::error, libftl::xml::blueprints::result>
    load(std::istream &);
}

#endif
