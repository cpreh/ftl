#ifndef LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_PARSE_HPP_INCLUDED

#include <libftl/impl/xml/types/document_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{

libftl::impl::xml::types::document
parse(
	std::string const &
);

}
}
}

#endif
