#ifndef LIBFTL_IMPL_XML_TYPED_NAMED_NODE_DERIVED_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NAMED_NODE_DERIVED_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/named_node_base.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/type_error.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Parser>
class named_node_derived : public libftl::impl::xml::typed::named_node_base<
                               libftl::impl::xml::typed::result_type<Parser>>
{
  FCPPT_NONMOVABLE(named_node_derived);
public:
  explicit named_node_derived(Parser &&_parser) : parser_{std::move(_parser)} {}
  ~named_node_derived() override = default;

  using result_type = libftl::impl::xml::typed::result_type<Parser>;
  using arg_type = libftl::impl::xml::node;

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(arg_type const &_arg) const override
  {
    return fcppt::deref(this->parser_).parse(_arg);
  }

  [[nodiscard]] std::string const &name() const override
  {
    return fcppt::deref(this->parser_).name();
  }
private:
  Parser parser_;
};
}

#endif
