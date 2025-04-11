#ifndef LIBFTL_XML_ERRORS_MISSING_NODE_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_MISSING_NODE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct missing_node
{
  std::string name_;

  [[nodiscard]]
  bool operator==(missing_node const &) const = default;
};
}

#endif
