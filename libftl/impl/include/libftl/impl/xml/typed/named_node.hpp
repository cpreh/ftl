#ifndef LIBFTL_IMPL_XML_TYPED_NAMED_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NAMED_NODE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/named_node_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
requires libftl::impl::xml::typed::parses<Parser, libftl::impl::xml::node>
class named_node
{
public:
  using result_type = libftl::impl::xml::typed::result_type<Parser>;

  using arg_type = libftl::impl::xml::node;

  named_node(std::string &&_name, Parser &&_parser)
      : name_{std::move(_name)}, parser_{std::move(_parser)}
  {
  }

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    return fcppt::deref(this->parser_).parse(_node);
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }

private:
  std::string name_;
  Parser parser_;
};

template <typename Parser>
named_node(std::string &&, Parser &&) -> named_node<Parser>;
}

#endif
