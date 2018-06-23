#include <libftl/impl/xml/types/document.hpp>
#include <libftl/impl/xml/types/document_output.hpp>
#include <libftl/impl/xml/types/node.hpp>
#include <libftl/impl/xml/types/node_output.hpp>
#include <fcppt/container/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


std::ostream &
libftl::impl::xml::types::operator<<(
	std::ostream &_stream,
	libftl::impl::xml::types::document const &_document
)
{
	return
		_stream
		<<
		fcppt::container::output(
			_document.nodes
		);
}
