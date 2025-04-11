#ifndef LIBFTL_IMPL_XML_TYPED_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/parses.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/mismatched_tags.hpp>
#include <fcppt/deref.hpp>
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

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    if (_node.opening_tag_ != this->name_)
    {
      return fcppt::either::make_failure<result_type>(libftl::xml::type_error{
          libftl::xml::type_error::variant{libftl::xml::errors::mismatched_tags{
              .location_ = _node.location_,
              .expected_tag_ = this->name_,
              .read_tag_ = _node.opening_tag_}}});
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
