#ifndef LIBFTL_IMPL_XML_TYPED_MAKE_NAMED_NODE_DERIVED_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_MAKE_NAMED_NODE_DERIVED_HPP_INCLUDED

#include <libftl/impl/xml/typed/named_node_base.hpp>
#include <libftl/impl/xml/typed/named_node_derived.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
[[nodiscard]] inline fcppt::unique_ptr<libftl::impl::xml::typed::named_node_base<
    libftl::impl::xml::typed::result_type<std::remove_cvref_t<Parser>>>>
make_named_node_derived(Parser &&_parser)
{
  return fcppt::unique_ptr_to_base<libftl::impl::xml::typed::named_node_base<
      libftl::impl::xml::typed::result_type<std::remove_cvref_t<Parser>>>>(
      fcppt::make_unique_ptr<
          libftl::impl::xml::typed::named_node_derived<std::remove_cvref_t<Parser>>>(
          std::forward<Parser>(_parser)));
}
}
#endif
