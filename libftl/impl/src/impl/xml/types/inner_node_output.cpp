#include <libftl/impl/xml/spirit/variant_output.hpp>
#include <libftl/impl/xml/types/attribute_output.hpp>
#include <libftl/impl/xml/types/inner_node.hpp>
#include <libftl/impl/xml/types/inner_node_output.hpp>
#include <libftl/impl/xml/types/leaf_node.hpp>
#include <libftl/impl/xml/types/node_output.hpp>
#include <libftl/impl/xml/types/node_vector.hpp>
#include <libftl/impl/xml/types/string.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


std::ostream &
libftl::impl::xml::types::operator<<(
	std::ostream &_stream,
	libftl::impl::xml::types::inner_node const &_node
)
{
	_stream
		<<
		"I<"
		<<
		_node.opening_tag
		<<
		" "
		<<
		fcppt::container::output(
			_node.attributes
		)
		<<
		">";

	fcppt::variant::match(
		_node.content.get(),
		[
			&_stream
		](
			libftl::impl::xml::types::node_vector const &_value
		)
		{
			_stream
				<<
				fcppt::container::output(
					_value
				);
		},
		[
			&_stream
		](
			libftl::impl::xml::types::string const &_value
		)
		{
			_stream
				<<
				_value;
		}
	);

	return
		_stream
		<<
		"</"
		<<
		_node.closing_tag
		<<
		">";
}
