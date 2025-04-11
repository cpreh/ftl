#ifndef LIBFTL_XML_ERRORS_ALTERNATIVE_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_ALTERNATIVE_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/type_error_fwd.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct alternative
{
  LIBFTL_DETAIL_SYMBOL
  explicit alternative(std::vector<fcppt::recursive<libftl::xml::type_error>> &&);

  std::vector<fcppt::recursive<libftl::xml::type_error>> errors_;

  [[nodiscard]]
  bool operator==(alternative const &) const;
};
}

#endif
