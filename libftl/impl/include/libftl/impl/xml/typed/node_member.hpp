#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_HPP_INCLUDED

#include <libftl/impl/xml/node_remember_fwd.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <libftl::impl::xml::typed::required, typename Attributes, typename Content>
class node_member
{
public:
  using inner_result_type = fcppt::tuple::object<
      libftl::impl::xml::typed::result_type<Attributes>,
      libftl::impl::xml::typed::result_type<Content>>;

  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::required::no);

  using result_type = std::
      conditional_t<is_optional, fcppt::optional::object<inner_result_type>, inner_result_type>;

  node(std::string &&_name, Attributes &&_attributes, Content &&_content)
      : name_{std::move(_name)}, attributes_{std::move(_attributes)}, content_{std::move(_content)}
  {
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }
  [[nodiscard]] Attributes const &attributes() const { return this->attributes_; }
  [[nodiscard]] Concent const &content() const { return this->content_; }
private:
  std::string name_;
  Attributes attributes_;
  Content content_;
};

template <libftl::impl::xml::typed::required Required, typename Attributes, typename Content>
node_member(Attributes &&, Content &&) -> node_member<Required, Attributes, Content>;
}

#endif
