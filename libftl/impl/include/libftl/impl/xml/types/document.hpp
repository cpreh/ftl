#ifndef LIBFTL_IMPL_XML_TYPES_DOCUMENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_DOCUMENT_HPP_INCLUDED

#include <libftl/impl/xml/types/document_fwd.hpp>
#include <libftl/impl/xml/types/node_vector.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{
namespace types
{

class document
{
public:
	document();

	explicit
	document(
		libftl::impl::xml::types::node_vector const &
	);

	libftl::impl::xml::types::node_vector nodes;
};

}
}
}
}

#endif
