#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/typed/attribute_fwd.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <typeinfo>
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
  explicit attribute(std::string &&_name) : name_{std::move(_name)} {}

  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::required::no);

  using result_type = Type;

  [[nodiscard]] std::string const &name() const { return this->name_; }

  [[nodiscard]] fcppt::either::object<libftl::error, Type>
  parse(libftl::impl::xml::attribute const &_attribute) const
  {
    return fcppt::either::from_optional(
        fcppt::extract_from_string<Type>(_attribute.value_),
        [&_attribute]
        {
          return libftl::error{
              fcppt::string{FCPPT_TEXT("Failed to convert ")} +
              fcppt::from_std_string(_attribute.name()) + FCPPT_TEXT(" to type ") +
              fcppt::from_std_string(fcppt::type_name_from_info(typeid(Type))) +
              FCPPT_TEXT(".")};
        });
  }
private:
  std::string name_;
};

}

#endif
