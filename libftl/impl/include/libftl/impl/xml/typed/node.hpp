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
template <typename Parser>
requires libftl::impl::xml::typed::parses<Parser, libftl::impl::xml::node>
class node
{
public:
  using result_type = libftl::impl::xml::typed::result_type<Parser>;

  using arg_type = libftl::impl::xml::node;

  node(std::string &&_name, Parser &&_parser)
      : name_{std::move(_name)}, parser_{std::move(_parser)}
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

    return fcppt::deref(this->parser_).parse(_node);
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }

private:
  std::string name_;
  Parser parser_;
};

template <typename Parser>
node(std::string &&, Parser &&) -> node<Parser>;
}

#endif
