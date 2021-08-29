#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_FWD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_FWD_HPP_INCLUDED

#include <libftl/impl/xml/inner_node_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace libftl::impl::xml::typed
{
template <libftl::impl::xml::typed::required, typename Attributes, typename Content>
requires libftl::impl::xml::typed::parses<Content,fcppt::optional::object<libftl::impl::xml::inner_node>>
class node_member;
}

#endif