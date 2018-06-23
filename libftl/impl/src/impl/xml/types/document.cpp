#include <libftl/impl/xml/types/document.hpp>
#include <libftl/impl/xml/types/node_vector.hpp>

// TODO
#include <libftl/impl/xml/types/node.hpp>


libftl::impl::xml::types::document::document()
:
	nodes{}
{
}

libftl::impl::xml::types::document::document(
	libftl::impl::xml::types::node_vector const &_nodes
)
:
	nodes(
		_nodes
	)
{
}
