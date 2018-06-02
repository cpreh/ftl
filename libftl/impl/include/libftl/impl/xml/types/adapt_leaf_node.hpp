#ifndef LIBFTL_IMPL_XML_TYPES_ADAPT_LEAF_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_ADAPT_LEAF_NODE_HPP_INCLUDED

#include <libftl/impl/xml/types/attribute_vector.hpp>
#include <libftl/impl/xml/types/leaf_node.hpp>
#include <libftl/impl/xml/types/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <fcppt/config/external_end.hpp>


BOOST_FUSION_ADAPT_STRUCT(
	libftl::impl::xml::types::leaf_node,
	(libftl::impl::xml::types::string, name),
	(libftl::impl::xml::types::attribute_vector, attributes),
)

#endif
