#ifndef LIBFTL_IMPL_XML_TYPED_MAKE_AS_STRUCT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_MAKE_AS_STRUCT_HPP_INCLUDED

#include <libftl/impl/xml/typed/as_struct.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Result, typename Parser>
[[nodiscard]] inline libftl::impl::xml::typed::as_struct<Result, std::remove_cvref_t<Parser>>
make_as_struct(Parser &&_parser)
{
  return libftl::impl::xml::typed::as_struct<Result, std::remove_cvref_t<Parser>>{
      std::forward<Parser>(_parser)};
}
}

#endif
