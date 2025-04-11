#ifndef LIBFTL_XML_ERRORS_NOT_EMPTY_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_NOT_EMPTY_HPP_INCLUDED

namespace libftl::xml::errors
{
struct not_empty
{
  [[nodiscard]]
  bool operator==(not_empty const &) const = default;
};
}

#endif
