#ifndef LIBFTL_IMPL_XML_TYPED_MAKE_NODE_MEMBER_IMPL_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_MAKE_NODE_MEMBER_IMPL_HPP_INCLUDED

#include <libftl/impl/xml/typed/node_member.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <libftl::impl::xml::typed::required Required, typename Parser>
[[nodiscard]] inline libftl::impl::xml::typed::node_member<Required, std::remove_cvref_t<Parser>>
make_node_member_impl(std::string &&_name, Parser &&_parser)
{
  return libftl::impl::xml::typed::node_member<Required, std::remove_cvref_t<Parser>>{
      std::move(_name), std::forward<Parser>(_parser)};
}
}
#endif
