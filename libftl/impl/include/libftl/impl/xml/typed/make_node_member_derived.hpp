#ifndef LIBFTL_IMPL_XML_TYPED_MAKE_NODE_MEMBER_DERIVED_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_MAKE_NODE_MEMBER_DERIVED_HPP_INCLUDED

#include <libftl/impl/xml/typed/node_member_base.hpp>
#include <libftl/impl/xml/typed/node_member_derived.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
[[nodiscard]] inline fcppt::unique_ptr<libftl::impl::xml::typed::node_member_base<
    std::remove_cvref_t<fcppt::deref_type<Parser>>::is_required,
    libftl::impl::xml::typed::result_type<std::remove_cvref_t<Parser>>>>
make_node_member_derived(Parser &&_parser)
{
  return fcppt::unique_ptr_to_base<libftl::impl::xml::typed::node_member_base<
      std::remove_cvref_t<fcppt::deref_type<Parser>>::is_required,
      libftl::impl::xml::typed::result_type<std::remove_cvref_t<Parser>>>>(
      fcppt::make_unique_ptr<
          libftl::impl::xml::typed::node_member_derived<std::remove_cvref_t<Parser>>>(
          std::forward<Parser>(_parser)));
}
}
#endif
