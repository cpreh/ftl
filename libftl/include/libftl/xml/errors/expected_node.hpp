#ifndef LIBFTL_XML_ERRORS_EXPECTED_NODE_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_EXPECTED_NODE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct expected_node
{
  std::string content_;

  [[nodiscard]]
  bool operator==(expected_node const &) const = default;
};
}

#endif
