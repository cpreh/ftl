#ifndef LIBFTL_IMPL_XML_TYPED_REQUIRED_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_REQUIRED_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
enum class required : std::uint8_t
{
  no,
  yes
};
}

#endif
