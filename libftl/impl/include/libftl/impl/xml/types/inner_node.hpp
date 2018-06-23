#ifndef LIBFTL_IMPL_XML_TYPES_INNER_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_INNER_NODE_HPP_INCLUDED

#include <libftl/impl/xml/types/inner_node_fwd.hpp>
#include <libftl/impl/xml/types/node_content_wrapper.hpp>
#include <libftl/impl/xml/types/string.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace types
{

class inner_node
{
public:
	libftl::impl::xml::types::node_content_wrapper content;

	libftl::impl::xml::types::string closing_tag;
};

}
}
}
}

#endif
