#include <libftl/impl/xml/types/attribute_output.hpp>
#include <libftl/impl/xml/types/inner_node_output.hpp>
#include <libftl/impl/xml/types/node.hpp>
#include <libftl/impl/xml/types/node_output.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/optional/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


std::ostream &
libftl::impl::xml::types::operator<<(
	std::ostream &_stream,
	libftl::impl::xml::types::node const &_node
)
{
	return
		_stream
		<<
		"<('"
		<<
		_node.opening_tag
		<<
		"' "
		<<
		fcppt::container::output(
			_node.attributes
		)
		<<
		_node.content
		<<
		")>";
}
