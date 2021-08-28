#ifndef LIBFTL_IMPL_XML_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_ATTRIBUTE_HPP_INCLUDED

#include <libftl/impl/xml/attribute_fwd.hpp>
#include <fcppt/parse/location.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct attribute
{
  attribute(
      std::string &&_name,
      std::string &&_value)
      : attribute(fcppt::optional::nothing{},std::move(_name),std::move(_value))
  {
  }

  attribute(
      fcppt::optional::object<fcppt::parse::location> const _location,
      std::string &&_name,
      std::string &&_value)
      : location_{_location}, name_{std::move(_name)}, value_{std::move(_value)}
  {
  }

  fcppt::optional::object<fcppt::parse::location> location_;

  std::string name_;

  std::string value_;

  [[nodiscard]] std::string const &name() const { return this->name_; }
};
}

#endif
