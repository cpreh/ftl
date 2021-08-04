#ifndef LIBFTL_IMPL_XML_INNER_NODE_CONTENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_INNER_NODE_CONTENT_HPP_INCLUDED

#include <libftl/impl/xml/node_vector.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
using inner_node_content = fcppt::variant::object<libftl::impl::xml::node_vector, std::string>;
}

#endif
