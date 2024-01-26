#ifndef LIBFTL_IMPL_XML_TYPED_NAMED_NODE_FWD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NAMED_NODE_FWD_HPP_INCLUDED

#include <libftl/impl/xml/node_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp> // IWYU pragma: keep

namespace libftl::impl::xml::typed
{
template <typename Parser>
requires libftl::impl::xml::typed::parses<Parser, libftl::impl::xml::node>
class named_node;

}

#endif
