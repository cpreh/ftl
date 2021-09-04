#ifndef LIBFTL_IMPL_XML_TYPED_MAKE_CONSTRUCT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_MAKE_CONSTRUCT_HPP_INCLUDED

#include <libftl/impl/xml/typed/construct.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Result, typename Arg, typename Parser>
[[nodiscard]] inline libftl::impl::xml::typed::construct<Result, Arg, std::remove_cvref_t<Parser>>
make_construct(Parser &&_parser)
{
  return libftl::impl::xml::typed::construct<Result, Arg, std::remove_cvref_t<Parser>>{
      std::forward<Parser>(_parser)};
}
}

#endif
