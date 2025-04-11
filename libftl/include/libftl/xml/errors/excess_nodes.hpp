#ifndef LIBFTL_XML_ERRORS_EXCESS_NODES_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_EXCESS_NODES_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct excess_nodes
{
  std::string name_;

  [[nodiscard]]
  bool operator==(excess_nodes const &) const = default;
};
}

#endif
