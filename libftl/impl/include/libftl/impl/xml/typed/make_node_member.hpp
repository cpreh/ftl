#ifndef LIBFTL_IMPL_XML_TYPED_MAKE_NODE_MEMBER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_MAKE_NODE_MEMBER_HPP_INCLUDED

#include <libftl/impl/xml/typed/make_node_member_impl.hpp>
#include <libftl/impl/xml/typed/node_content.hpp>
#include <libftl/impl/xml/typed/node_member.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <libftl::impl::xml::typed::required Required, typename Attributes, typename Content>
[[nodiscard]] inline libftl::impl::xml::typed::node_member<
    Required,
    libftl::impl::xml::typed::
        node_content<std::remove_cvref_t<Attributes>, std::remove_cvref_t<Content>>>
make_node_member(std::string &&_name, Attributes &&_attributes, Content &&_content)
{
  return libftl::impl::xml::typed::make_node_member_impl<Required>(
      std::move(_name),
      libftl::impl::xml::typed::node_content{
          std::forward<Attributes>(_attributes), std::forward<Content>(_content)});
}
}
#endif
