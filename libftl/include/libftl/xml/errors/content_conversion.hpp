#ifndef LIBFTL_XML_ERRORS_CONTENT_CONVERSION_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_CONTENT_CONVERSION_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <string>
#include <typeindex>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct content_conversion
{
  std::type_index type_;

  std::string content_;

  [[nodiscard]]
  bool operator==(content_conversion const &) const = default;
};
}

#endif
