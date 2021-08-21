#ifndef LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ATTRIBUTE_HPP_INCLUDED

#include <libftl/impl/xml/typed/attribute_fwd.hpp>
#include <libftl/impl/xml/typed/attribute_required.hpp>
#include <fcppt/optional/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <
    typename Type,
    libftl::impl::xml::typed::attribute_required Required>
class attribute
{
public:
  explicit attribute(std::string &&_name) : name_{std::move(_name)} {}

  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::attribute_required::no);

  using result_type = std::conditional_t<is_optional, fcppt::optional::object<Type>, Type>;

  [[nodiscard]] std::string const &name() const { return this->name_; }
private:
  std::string name_;
};

}

#endif
