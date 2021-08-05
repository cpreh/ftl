#ifndef LIBFTL_IMPL_XML_TYPED_PARSE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_PARSE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/object.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
[[nodiscard]] inline fcppt::either::object<libftl::error, typename Parser::result_type>
parse(Parser const &_parser, fcppt::optional::object<libftl::impl::xml::inner_node> const &_node)
{
  return fcppt::deref(_parser).parse(_node);
}
}

#endif
