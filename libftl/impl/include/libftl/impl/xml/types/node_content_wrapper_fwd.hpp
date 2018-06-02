#ifndef LIBFTL_IMPL_XML_TYPES_NODE_CONTENT_WRAPPER_FWD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_NODE_CONTENT_WRAPPER_FWD_HPP_INCLUDED

#include <libftl/impl/xml/spirit/variant_fwd.hpp>
#include <libftl/impl/xml/types/node_content_fwd.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace types
{

typedef
libftl::impl::xml::spirit::variant<
	libftl::impl::xml::types::node_content
>
node_content_wrapper;

}
}
}
}

#endif
