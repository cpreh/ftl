#ifndef LIBFTL_XML_ANIMATIONS_LOAD_HPP_INCLUDED
#define LIBFTL_XML_ANIMATIONS_LOAD_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/xml/animations/result.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::animations
{
[[nodiscard]] LIBFTL_DETAIL_SYMBOL
    fcppt::either::object<libftl::xml::error, libftl::xml::animations::result>
    load(std::istream &);
}

#endif
