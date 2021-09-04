#ifndef LIBFTL_IMPL_XML_TYPED_IS_NODE_MEMBER_LIST_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_IS_NODE_MEMBER_LIST_HPP_INCLUDED

#include <libftl/impl/xml/typed/node_member_list_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Type>
struct is_node_member_list : std::false_type
{
};

template <typename Parser>
struct is_node_member_list<libftl::impl::xml::typed::node_member_list<Parser>> : std::true_type
{
};
}

#endif
