#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_HPP_INCLUDED

#include <libftl/impl/xml/attribute.hpp>
#include <libftl/impl/xml/typed/attribute_fwd.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/attribute_conversion.hpp>
#include <fcppt/extract_from_string_fmt.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <string>
#include <typeinfo> // IWYU pragma: keep
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <
    typename Type,
    libftl::impl::xml::typed::required Required>
class attribute
{
public:
  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::required::no);

  using result_type = Type;

  explicit attribute(std::string &&_name) : name_{std::move(_name)} {}

  [[nodiscard]] std::string const &name() const { return this->name_; }

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, Type>
  parse(libftl::impl::xml::attribute const &_attribute) const
  {
    return fcppt::either::from_optional(
        fcppt::extract_from_string_fmt<Type>(_attribute.value_, std::ios_base::boolalpha),
        [&_attribute]
        {
          return libftl::xml::type_error{
              libftl::xml::type_error::variant{libftl::xml::errors::attribute_conversion{
                  .location_ = _attribute.location_,
                  .type_ = typeid(Type),
                  .name_ = _attribute.name(),
                  .value_ = _attribute.value_}}};
        });
  }
private:
  std::string name_;
};

}

#endif
