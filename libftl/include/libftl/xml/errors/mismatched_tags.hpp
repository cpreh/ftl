#ifndef LIBFTL_XML_ERRORS_MISMATCHED_TAGS_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_MISMATCHED_TAGS_HPP_INCLUDED

#include <fcppt/optional/comparison.hpp> // IWYU pragma: keep
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/location.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::xml::errors
{
struct mismatched_tags
{
  fcppt::optional::object<fcppt::parse::location> location_;

  std::string expected_tag_;

  std::string read_tag_;

  [[nodiscard]]
  bool operator==(mismatched_tags const &) const = default;
};
}

#endif
