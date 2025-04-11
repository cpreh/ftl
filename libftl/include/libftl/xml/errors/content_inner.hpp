#ifndef LIBFTL_XML_ERRORS_CONTENT_INNER_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_CONTENT_INNER_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <typeindex>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct content_inner
{
  std::type_index type_;

  [[nodiscard]]
  bool operator==(content_inner const &) const = default;
};
}

#endif
