#ifndef LIBFTL_XML_ERRORS_CONTENT_EMPTY_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_CONTENT_EMPTY_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <typeindex>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct content_empty
{
  std::type_index type_;

  [[nodiscard]]
  bool operator==(content_empty const &) const = default;
};
}

#endif
