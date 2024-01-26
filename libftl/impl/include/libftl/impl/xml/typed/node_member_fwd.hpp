#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_FWD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_FWD_HPP_INCLUDED

#include <libftl/impl/xml/node_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/required.hpp>

namespace libftl::impl::xml::typed
{
template <libftl::impl::xml::typed::required, typename Parser>
requires libftl::impl::xml::typed::parses<Parser,libftl::impl::xml::node>
class node_member; // IWYU pragma: export
}

#endif
