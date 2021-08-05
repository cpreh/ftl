#ifndef LIBFTL_IMPL_XML_TYPED_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/parse.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

/*
namespace libftl::impl::xml::typed
{
template <typename Attributes, typename Content>
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
  parse(libftl::impl::xml::node const &_node)
  {
    if (_node.opening_tag_ != this->name_)
    {
      return fcppt::either::make_failure<result_type>(
          fcppt::string{FCPPT_TEXT("Mismatched tags, expected ")} +
          fcppt::from_std_string(this->name_) + FCPPT_TEXT(", got ") +
          fcppt::from_std_string(_node.opening_tag) + FCPPT_TEXT("."));
    }

    return fcppt::either::bind(
        libftl::impl::xml::typed::parse(this->attributes_, _node.attributes_),
        [](libftl::impl::xml::typed::result_type<Attributes> &&_attributes_result)
        {
          return fcppt::either::map(
              libftl::impl::xml::typed::parse(this->content_, _node.content_),
              [&_attributes_result](
                  libftl::impl::xml::typed::result_type<Content> &&_content_result) {
                return result_type{std::move(_attributes_result), std::move(_content_result)};
              });
        });
  }

private:
  std::string name_;
  Attributes attributes_;
  Content content_;
};
}*/

#endif
