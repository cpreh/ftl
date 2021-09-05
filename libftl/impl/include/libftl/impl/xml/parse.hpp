#ifndef LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
[[nodiscard]]
fcppt::either::object<libftl::error, libftl::impl::xml::document> parse(std::istream &);

}

#endif
