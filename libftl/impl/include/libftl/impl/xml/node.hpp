#ifndef LIBFTL_IMPL_XML_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_NODE_HPP_INCLUDED

#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node_fwd.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct node
{
  std::string opening_tag_;

  std::vector<libftl::impl::xml::attribute> attributes_;

  fcppt::optional::object<libftl::impl::xml::inner_node> content_;
};

}

#endif
