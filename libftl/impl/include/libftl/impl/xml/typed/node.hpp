#ifndef LIBFTL_IMPL_XML_TYPED_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Attributes, typename Content>
requires libftl::impl::xml::typed::parses<Content,fcppt::optional::object<libftl::impl::xml::inner_node>>
class node
{
public:
  using result_type = fcppt::tuple::object<
      libftl::impl::xml::typed::result_type<Attributes>,
      libftl::impl::xml::typed::result_type<Content>>;

  node(std::string &&_name, Attributes &&_attributes, Content &&_content)
      : name_{std::move(_name)}, attributes_{std::move(_attributes)}, content_{std::move(_content)}
  {
  }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    if (_node.opening_tag_ != this->name_)
    {
      return fcppt::either::make_failure<result_type>(libftl::error{
          fcppt::string{FCPPT_TEXT("Mismatched tags, expected ")} +
          fcppt::from_std_string(this->name_) + FCPPT_TEXT(", got ") +
          fcppt::from_std_string(_node.opening_tag_) + FCPPT_TEXT(".")});
    }

    return fcppt::either::bind(
        fcppt::deref(this->attributes_).parse(_node.attributes_),
        [this, &_node](libftl::impl::xml::typed::result_type<Attributes> &&_attributes_result)
        {
          return fcppt::either::map(
              fcppt::deref(this->content_).parse(_node.content_),
              [&_attributes_result](
                  libftl::impl::xml::typed::result_type<Content> &&_content_result) {
                return result_type{std::move(_attributes_result), std::move(_content_result)};
              });
        });
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }
private:
  std::string name_;
  Attributes attributes_;
  Content content_;
};

template <typename Attributes, typename Content>
node(Attributes &&, Content &&) -> node<Attributes, Content>;
}

#endif
