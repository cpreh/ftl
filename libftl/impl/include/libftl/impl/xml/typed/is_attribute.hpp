#ifndef LIBFTL_IMPL_XML_TYPED_IS_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_IS_ATTRIBUTE_HPP_INCLUDED

#include <libftl/impl/xml/typed/attribute_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Type>
struct is_attribute : std::false_type
{
};

template <typename Type, libftl::impl::xml::typed::attribute_required Required>
struct is_attribute<libftl::impl::xml::typed::attribute<Type, Required>> : std::true_type
{
};

}

#endif
