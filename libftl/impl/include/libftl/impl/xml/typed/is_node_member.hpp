#ifndef LIBFTL_IMPL_XML_TYPED_IS_NODE_MEMBER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_IS_NODE_MEMBER_HPP_INCLUDED

#include <libftl/impl/xml/typed/node_member_fwd.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Type>
struct is_node_member : std::false_type
{
};

template <libftl::impl::xml::typed::required Required, typename Attributes, typename Content>
struct is_node_member<libftl::impl::xml::typed::node_member<Required, Attributes, Content>>
    : std::true_type
{
};
}

#endif
