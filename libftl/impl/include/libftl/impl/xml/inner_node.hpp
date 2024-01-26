#ifndef LIBFTL_IMPL_XML_INNER_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_INNER_NODE_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/inner_node_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct inner_node
{
  LIBFTL_DETAIL_SYMBOL inner_node(libftl::impl::xml::inner_node_content &&, std::string &&);

  libftl::impl::xml::inner_node_content content_;

  std::string closing_tag_;
};
}

#endif
