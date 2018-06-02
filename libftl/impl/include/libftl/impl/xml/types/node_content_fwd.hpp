#ifndef LIBFTL_IMPL_XML_TYPES_NODE_CONTENT_FWD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_NODE_CONTENT_FWD_HPP_INCLUDED

#include <libftl/impl/xml/types/node_vector.hpp>
#include <libftl/impl/xml/types/string.hpp>
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
	libftl::impl::xml::types::node_vector,
	libftl::impl::xml::types::string
>
node_content;

}
}
}
}

#endif
