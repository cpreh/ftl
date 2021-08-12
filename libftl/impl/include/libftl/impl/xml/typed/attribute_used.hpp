#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_USED_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_USED_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
FCPPT_MAKE_STRONG_TYPEDEF(fcppt::optional::object<std::string>, attribute_used);
}

#endif
