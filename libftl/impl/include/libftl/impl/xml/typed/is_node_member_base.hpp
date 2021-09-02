#ifndef LIBFTL_IMPL_XML_TYPED_IS_NODE_MEMBER_BASE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_IS_NODE_MEMBER_BASE_HPP_INCLUDED

#include <libftl/impl/xml/typed/node_member_base_fwd.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Type>
struct is_node_member_base : std::false_type
{
};

template <libftl::impl::xml::typed::required Required, typename Result>
struct is_node_member_base<libftl::impl::xml::typed::node_member_base<Required, Result>>
    : std::true_type
{
};
}

#endif
