#include <libftl/impl/xml/document.hpp>


libftl::impl::xml::document::document()
:
	nodes_{}
{
}

libftl::impl::xml::document::document(
	node_vector const &_nodes
)
:
	nodes_(
		_nodes
	)
{
}
