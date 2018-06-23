#include <libftl/impl/xml/types/attribute.hpp>
#include <libftl/impl/xml/types/attribute_output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


std::ostream &
libftl::impl::xml::types::operator<<(
	std::ostream &_stream,
	libftl::impl::xml::types::attribute const &_attribute
)
{
	return
		_stream
		<<
		_attribute.name
		<<
		"=\""
		<<
		_attribute.value
		<<
		'"';
}
