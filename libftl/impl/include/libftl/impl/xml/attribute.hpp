#ifndef LIBFTL_IMPL_XML_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_ATTRIBUTE_HPP_INCLUDED

#include <libftl/impl/xml/attribute_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct attribute
{
  std::string name_;

  std::string value_;
};
}

#endif
