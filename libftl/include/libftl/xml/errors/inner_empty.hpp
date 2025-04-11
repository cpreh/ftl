#ifndef LIBFTL_XML_ERRORS_INNER_EMPTY_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_INNER_EMPTY_HPP_INCLUDED

namespace libftl::xml::errors
{
struct inner_empty
{
  [[nodiscard]]
  bool operator==(inner_empty const &) const = default;
};
}

#endif
