#ifndef LIBFTL_IMPL_XML_TYPES_ADAPT_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_ADAPT_NODE_HPP_INCLUDED

#include <libftl/impl/xml/types/attribute_vector.hpp>
#include <libftl/impl/xml/types/node.hpp>
#include <libftl/impl/xml/types/optional_inner_node.hpp>
#include <libftl/impl/xml/types/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <fcppt/config/external_end.hpp>


BOOST_FUSION_ADAPT_STRUCT(
	libftl::impl::xml::types::node,
	(libftl::impl::xml::types::string, opening_tag),
	(libftl::impl::xml::types::attribute_vector, attributes)
	(libftl::impl::xml::types::optional_inner_node, content)
)

#endif
