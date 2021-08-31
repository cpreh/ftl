#ifndef LIBFTL_IMPL_XML_TYPED_MAKE_DERIVED_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_MAKE_DERIVED_HPP_INCLUDED

#include <fcppt/unique_ptr_to_base.hpp>
#include <libftl/impl/xml/typed/arg_type.hpp>
#include <libftl/impl/xml/typed/base.hpp>
#include <libftl/impl/xml/typed/derived.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
[[nodiscard]] inline fcppt::unique_ptr<libftl::impl::xml::typed::base<
    libftl::impl::xml::typed::result_type<Parser>,
    libftl::impl::xml::typed::arg_type<Parser>>>
make_derived(Parser &&_parser)
{
  return fcppt::unique_ptr_to_base<libftl::impl::xml::typed::base<
      libftl::impl::xml::typed::result_type<Parser>,
      libftl::impl::xml::typed::arg_type<Parser>>>(
      fcppt::make_unique_ptr<libftl::impl::xml::typed::derived<std::remove_cvref_t<Parser>>>(
          std::forward<Parser>(_parser)));
}
}

#endif
