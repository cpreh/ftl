#ifndef LIBFTL_IMPL_XML_MAKE_INNER_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_MAKE_INNER_NODE_HPP_INCLUDED

#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/inner_node_content.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{

inline
libftl::impl::xml::inner_node
make_inner_node(libftl::impl::xml::inner_node_content &&_inner)
{
  return libftl::impl::xml::inner_node(std::move(_inner),std::string{});
}

}

#endif
