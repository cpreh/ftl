#ifndef LIBFTL_XML_ERRORS_UNUSED_NODES_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_UNUSED_NODES_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <set>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct unused_nodes
{
  std::set<std::string> nodes_;

  [[nodiscard]]
  bool operator==(unused_nodes const &) const = default;
};
}

#endif
