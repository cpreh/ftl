#ifndef LIBFTL_IMPL_XML_TYPES_INNER_NODE_OUTPUT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_INNER_NODE_OUTPUT_HPP_INCLUDED

#include <libftl/impl/xml/types/inner_node_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace types
{

std::ostream &
operator<<(
	std::ostream &,
	libftl::impl::xml::types::inner_node const &
);

}
}
}
}

#endif
