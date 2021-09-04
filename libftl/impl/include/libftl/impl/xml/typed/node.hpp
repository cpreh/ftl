#ifndef LIBFTL_IMPL_XML_TYPED_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/location_to_string.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Content>
requires libftl::impl::xml::typed::parses<Content, libftl::impl::xml::node>
class node
{
public:
  using result_type = libftl::impl::xml::typed::result_type<Content>;

  using arg_type = libftl::impl::xml::node;

  node(std::string &&_name, Content &&_content)
      : name_{std::move(_name)}, content_{std::move(_content)}
  {
  }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    if (_node.opening_tag_ != this->name_)
    {
      return fcppt::either::make_failure<result_type>(libftl::error{
          libftl::impl::xml::location_to_string(_node.location_) +
          fcppt::string{FCPPT_TEXT("Mismatched tags, expected ")} +
          fcppt::from_std_string(this->name_) + FCPPT_TEXT(", got ") +
          fcppt::from_std_string(_node.opening_tag_) + FCPPT_TEXT(".")});
    }

    return fcppt::deref(this->content_).parse(_node);
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }

private:
  std::string name_;
  Content content_;
};

template <typename Content>
node(std::string &&, Content &&) -> node<Content>;
}

#endif
