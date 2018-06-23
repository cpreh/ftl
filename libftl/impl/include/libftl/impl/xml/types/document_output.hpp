#ifndef LIBFTL_IMPL_XML_TYPES_DOCUMENT_OUTPUT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_DOCUMENT_OUTPUT_HPP_INCLUDED

#include <libftl/impl/xml/types/document_fwd.hpp>
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
	libftl::impl::xml::types::document const &
);

}
}
}
}

#endif