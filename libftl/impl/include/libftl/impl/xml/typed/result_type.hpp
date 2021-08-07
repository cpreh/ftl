#ifndef LIBFTL_IMPL_XML_TYPED_RESULT_TYPE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_RESULT_TYPE_HPP_INCLUDED

namespace libftl::impl::xml::typed
{
template <typename Parser>
using result_type = typename Parser::result_type;

}

#endif
