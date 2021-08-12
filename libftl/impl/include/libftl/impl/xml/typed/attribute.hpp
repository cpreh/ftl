#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/typed/attribute_map.hpp>
#include <libftl/impl/xml/typed/attribute_required.hpp>
#include <libftl/impl/xml/typed/attribute_used.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/use.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <
    typename Type,
    libftl::impl::xml::typed::attribute_required Required =
        libftl::impl::xml::typed::attribute_required::yes>
class attribute
{
public:
  explicit attribute(std::string &&_name) : name_{std::move(_name)} {}

  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::attribute_required::no);

  using result_type = std::conditional_t<is_optional, fcppt::optional::object<Type>, Type>;

  [[nodiscard]] fcppt::tuple::object<
      libftl::impl::xml::typed::attribute_used,
      fcppt::either::object<libftl::error, result_type>>
  parse(libftl::impl::xml::typed::attribute_map const &_attributes) const
  {
    return fcppt::optional::maybe(
        fcppt::container::find_opt_mapped(_attributes, this->name_),
        [this]() -> fcppt::tuple::object<
                     libftl::impl::xml::typed::attribute_used,
                     fcppt::either::object<libftl::error, result_type>>
        {
          if constexpr(is_optional)
          {
            FCPPT_USE(this);
            return fcppt::tuple::make(
                libftl::impl::xml::typed::attribute_used{fcppt::optional::nothing{}},
                fcppt::either::make_success<libftl::error>(result_type{}));
          }
          else
          {
            return fcppt::tuple::make(
                libftl::impl::xml::typed::attribute_used{fcppt::optional::nothing{}},
                fcppt::either::make_failure<result_type>(libftl::error{
                    fcppt::string{FCPPT_TEXT("Missing attribute ")} +
                    fcppt::from_std_string(this->name_) + FCPPT_TEXT(".")}));
          }
        },
        [this](fcppt::reference<std::string const> const _mapped)
            -> fcppt::tuple::object<
                libftl::impl::xml::typed::attribute_used,
                fcppt::either::object<libftl::error, result_type>>
        {
          return fcppt::tuple::make(
              libftl::impl::xml::typed::attribute_used{fcppt::optional::make(this->name_)},
              fcppt::optional::maybe(
                  fcppt::extract_from_string<Type>(_mapped.get()),
                  [&_mapped]
                  {
                    return fcppt::either::make_failure<result_type>(libftl::error{
                        fcppt::string{FCPPT_TEXT("Failed to convert ")} +
                        fcppt::from_std_string(_mapped.get()) + FCPPT_TEXT(" to type ") +
                        fcppt::from_std_string(fcppt::type_name_from_info(typeid(Type))) +
                        FCPPT_TEXT(".")});
                  },
                  [](Type &&_result)
                  {
                    if constexpr (is_optional)
                    {
                      return fcppt::either::make_success<libftl::error>(
                          fcppt::optional::make(std::move(_result)));
                    }
                    else
                    {
                      return fcppt::either::make_success<libftl::error>(std::move(_result));
                    }
                  }));
        });
  }
private:
  std::string name_;
};

}

#endif
