#ifndef LIBFTL_IMPL_XML_TYPES_LEAF_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_LEAF_NODE_HPP_INCLUDED

#include <libftl/impl/xml/types/attribute_vector.hpp>
#include <libftl/impl/xml/types/leaf_node_fwd.hpp>
#include <libftl/impl/xml/types/string.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace types
{

class leaf_node
{
public:
	libftl::impl::xml::types::string name;

	libftl::impl::xml::types::attribute_vector attributes;
};

}
}
}
}

#endif
