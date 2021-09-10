#ifndef LIBFTL_IMPL_XML_TYPED_IS_NAMED_NODE_BASE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_IS_NAMED_NODE_BASE_HPP_INCLUDED

#include <libftl/impl/xml/typed/named_node_base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Type>
struct is_named_node_base : std::false_type
{
};

template <typename Result>
struct is_named_node_base<libftl::impl::xml::typed::named_node_base<Result>> : std::true_type
{
};
}

#endif
