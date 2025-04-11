#ifndef LIBFTL_XML_ERRORS_UNUSED_ATTRIBUTES_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_UNUSED_ATTRIBUTES_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct unused_attributes
{
  std::set<std::string> attributes_;

  [[nodiscard]]
  bool operator==(unused_attributes const &) const = default;
};
}

#endif
