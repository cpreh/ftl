#ifndef LIBFTL_IMPL_XML_TYPED_PARSES_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_PARSES_HPP_INCLUDED

#include <fcppt/deref.hpp>

namespace libftl::impl::xml::typed
{
template<typename Parser, typename Arg>
concept parses = requires(Parser const &_parser, Arg const &_arg)
{
  fcppt::deref(_parser).parse(_arg);
};

}

#endif
