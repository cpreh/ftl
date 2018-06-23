#ifndef LIBFTL_IMPL_XML_TYPES_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_NODE_HPP_INCLUDED

#include <libftl/impl/xml/types/attribute_vector.hpp>
#include <libftl/impl/xml/types/node_fwd.hpp>
#include <libftl/impl/xml/types/optional_inner_node.hpp>
#include <libftl/impl/xml/types/string.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace types
{

class node
{
public:
	libftl::impl::xml::types::string opening_tag;

	libftl::impl::xml::types::attribute_vector attributes;

	libftl::impl::xml::types::optional_inner_node content;
};

}
}
}
}

#endif
