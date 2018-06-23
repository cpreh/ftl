#include <libftl/impl/xml/types/attribute_output.hpp>
#include <libftl/impl/xml/types/leaf_node.hpp>
#include <libftl/impl/xml/types/leaf_node_output.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


std::ostream &
libftl::impl::xml::types::operator<<(
	std::ostream &_stream,
	libftl::impl::xml::types::leaf_node const &_leaf_node
)
{
	return
		_stream
		<<
		"L<"
		<<
		_leaf_node.name
		<<
		" "
		<<
		fcppt::container::output(
			_leaf_node.attributes
		)
		<<
		"/>";
}
