#ifndef LIBFTL_XML_ERRORS_ATTRIBUTE_CONVERSION_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_ATTRIBUTE_CONVERSION_HPP_INCLUDED

#include <fcppt/optional/object.hpp>
#include <fcppt/parse/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <typeindex>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct attribute_conversion
{
  fcppt::optional::object<fcppt::parse::location> location_;

  std::type_index type_;

  std::string name_;

  std::string value_;

  [[nodiscard]]
  bool operator==(attribute_conversion const &) const = default;
};
}

#endif
