#ifndef LIBFTL_IMPL_XML_TYPED_IS_NAMED_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_IS_NAMED_NODE_HPP_INCLUDED

#include <libftl/impl/xml/typed/named_node_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Type>
struct is_named_node : std::false_type
{
};

template <typename Parser>
struct is_named_node<libftl::impl::xml::typed::named_node<Parser>> : std::true_type
{
};
}

#endif
