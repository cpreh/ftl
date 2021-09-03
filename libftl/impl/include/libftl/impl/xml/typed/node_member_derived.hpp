#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_DERIVED_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_DERIVED_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/node_member_base.hpp>
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template<typename Parser>
class node_member_derived
:
  public libftl::impl::xml::typed::node_member_base<
    std::remove_cvref_t<fcppt::deref_type<Parser>>::is_required,
    libftl::impl::xml::typed::result_type<Parser>
  >
{
  FCPPT_NONMOVABLE(node_member_derived);
public:
  explicit node_member_derived(Parser &&_parser) : parser_{std::move(_parser)} {}
  ~node_member_derived() override = default;

  using result_type = libftl::impl::xml::typed::result_type<Parser>;
  using arg_type = std::vector<fcppt::reference<libftl::impl::xml::node const>>;

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
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
