#ifndef LIBFTL_IMPL_XML_DOCUMENT_OUTPUT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_DOCUMENT_OUTPUT_HPP_INCLUDED

#include <libftl/impl/xml/document_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
std::ostream &operator<<(std::ostream &, libftl::impl::xml::document const &);

}

#endif
