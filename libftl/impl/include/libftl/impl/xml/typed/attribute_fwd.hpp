#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_FWD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_FWD_HPP_INCLUDED

#include <libftl/impl/xml/typed/attribute_required.hpp>

namespace libftl::impl::xml::typed
{
template <
    typename Type,
    libftl::impl::xml::typed::attribute_required Required =
        libftl::impl::xml::typed::attribute_required::yes>
class attribute;
}

#endif
