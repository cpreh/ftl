#ifndef LIBFTL_IMPL_XML_TYPES_ADAPT_INNER_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPES_ADAPT_INNER_NODE_HPP_INCLUDED

#include <libftl/impl/xml/types/inner_node.hpp>
#include <libftl/impl/xml/types/node_content_wrapper.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <fcppt/config/external_end.hpp>


BOOST_FUSION_ADAPT_STRUCT(
	libftl::impl::xml::types::inner_node,
	(libftl::impl::xml::types::node_content_wrapper, content),
	(libftl::impl::xml::types::string, closing_tag),
)

#endif
