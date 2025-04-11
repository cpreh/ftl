#ifndef LIBFTL_XML_ERRORS_INVALID_NODE_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_INVALID_NODE_HPP_INCLUDED

#include <fcppt/optional/object.hpp>
#include <fcppt/parse/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct invalid_node
{
  fcppt::optional::object<fcppt::parse::location> location_;

  std::string name_;

  [[nodiscard]]
  bool operator==(invalid_node const &) const = default;
};
}

#endif
