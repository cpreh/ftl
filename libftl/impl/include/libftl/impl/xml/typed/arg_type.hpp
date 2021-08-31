#ifndef LIBFTL_IMPL_XML_TYPED_ARG_TYPE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ARG_TYPE_HPP_INCLUDED

#include <fcppt/deref_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
using arg_type = typename std::remove_cvref_t<fcppt::deref_type<Parser>>::arg_type;

}

#endif
