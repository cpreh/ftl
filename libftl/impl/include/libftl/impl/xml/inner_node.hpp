#ifndef LIBFTL_IMPL_XML_INNER_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_INNER_NODE_HPP_INCLUDED

#include <libftl/impl/xml/inner_node_fwd.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct inner_node
{
  fcppt::variant::object<libftl::impl::xml::node_vector, std::string> content_;

  std::string closing_tag_;
};
}

#endif
