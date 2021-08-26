#ifndef LIBFTL_IMPL_XML_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_ATTRIBUTE_HPP_INCLUDED

#include <libftl/impl/xml/attribute_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
struct attribute
{
  attribute(std::string &&_name, std::string &&_value)
      : name_{std::move(_name)}, value_{std::move(_value)}
  {
  }

  std::string name_;

  std::string value_;

  [[nodiscard]] std::string const &name() const { return this->name_; }

  [[nodiscard]] attribute const *operator->() const { return this; }
};
}

#endif
