#ifndef LIBFTL_IMPL_XML_TYPES_ADAPT_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_ADAPT_ATTRIBUTE_HPP_INCLUDED

#include <libftl/impl/xml/types/attribute.hpp>
#include <libftl/impl/xml/types/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <fcppt/config/external_end.hpp>


BOOST_FUSION_ADAPT_STRUCT(
	libftl::impl::xml::types::attribute,
	(libftl::impl::xml::types::string, name),
	(libftl::impl::xml::types::string, value),
)

#endif
