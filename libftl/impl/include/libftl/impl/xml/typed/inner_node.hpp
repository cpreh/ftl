#ifndef LIBFTL_IMPL_XML_TYPED_INNER_NODE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_INNER_NODE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template<typename Parser>
requires libftl::impl::xml::typed::parses<Parser,libftl::impl::xml::node_vector>
class inner_node
{
public:
  using result_type = libftl::impl::xml::typed::result_type<Parser>;

  explicit inner_node(Parser &&_parser) : parser_{std::move(_parser)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(fcppt::optional::object<libftl::impl::xml::inner_node> const &_node) const
  {
    return fcppt::optional::maybe(
        _node,
        []
        {
          return fcppt::either::make_failure<result_type>(
              libftl::error{fcppt::string{FCPPT_TEXT("Node is empty.")}});
        },
        [this](libftl::impl::xml::inner_node const &_inner_node)
        {
          return fcppt::variant::match(
              _inner_node.content_,
              [this](libftl::impl::xml::node_vector const &_nodes)
              { return fcppt::deref(this->parser_).parse(_nodes); },
              [](std::string const &_value)
              {
                return fcppt::either::make_failure<result_type>(libftl::error{fcppt::string{
                    FCPPT_TEXT("Expected inner node but content is ") +
                    fcppt::from_std_string(_value) + FCPPT_TEXT(".")}});
              });
        });
  }
private:
  Parser parser_;
};

template<typename Parser>
inner_node(Parser &&) -> inner_node<Parser>;
}

#endif
