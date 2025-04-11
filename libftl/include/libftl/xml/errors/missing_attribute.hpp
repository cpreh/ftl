#ifndef LIBFTL_XML_ERRORS_MISSING_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_MISSING_ATTRIBUTE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct missing_attribute
{
  std::string name_;

  [[nodiscard]]
  bool operator==(missing_attribute const &) const = default;
};
}

#endif
