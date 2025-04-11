#ifndef LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED

#include <libftl/impl/xml/document.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/parse/parse_stream_error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
[[nodiscard]]
fcppt::either::object<fcppt::parse::parse_stream_error<char>, libftl::impl::xml::document>
parse(std::istream &);
}

#endif
