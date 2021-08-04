#ifndef LIBFTL_IMPL_XML_INNER_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_INNER_NODE_HPP_INCLUDED

#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/inner_node_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct inner_node
{
  inner_node(libftl::impl::xml::inner_node_content &&_content, std::string &&_closing_tag)
      : content_{std::move(_content)}, closing_tag_{std::move(_closing_tag)}
  {
  }

  libftl::impl::xml::inner_node_content content_;

  std::string closing_tag_;
};
}

#endif
