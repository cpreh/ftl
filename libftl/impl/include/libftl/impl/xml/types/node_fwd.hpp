#ifndef LIBFTL_IMPL_XML_TYPES_NODE_FWD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_NODE_FWD_HPP_INCLUDED

#include <libftl/impl/xml/types/inner_node_fwd.hpp>
#include <libftl/impl/xml/types/leaf_node_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace types
{

typedef
fcppt::variant::variadic<
	libftl::impl::xml::types::leaf_node,
	libftl::impl::xml::types::inner_node
>
node;

}
}
}
}

#endif
