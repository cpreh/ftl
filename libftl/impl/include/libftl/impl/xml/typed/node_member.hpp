#ifndef LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NODE_MEMBER_HPP_INCLUDED

#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/node_member_fwd.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/parses.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/required.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/excess_nodes.hpp>
#include <libftl/xml/errors/missing_node.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/container/uncons.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/iterator/range.hpp>
#include <fcppt/range/empty.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <libftl::impl::xml::typed::required Required, typename Parser>
requires libftl::impl::xml::typed::parses<Parser,libftl::impl::xml::node>
class node_member
{
public:
  using result_type = libftl::impl::xml::typed::result_type<Parser>;

  using arg_type = std::vector<fcppt::reference<libftl::impl::xml::node const>>;

  static constexpr libftl::impl::xml::typed::required const is_required = Required;
  static constexpr bool const is_optional = (Required == libftl::impl::xml::typed::required::no);

  node_member(std::string &&_name, Parser &&_parser)
      : name_{std::move(_name)}, parser_{std::move(_parser)}
  {
  }

  [[nodiscard]] std::string const &name() const { return this->name_; }

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(std::vector<fcppt::reference<libftl::impl::xml::node const>> const &_nodes) const
  {
    return fcppt::either::bind(
        fcppt::either::from_optional(
            fcppt::container::uncons(_nodes),
            [this]
            {
              return libftl::xml::type_error{
                  libftl::xml::type_error::variant{libftl::xml::errors::missing_node{this->name_}}};
            }),
        [this](
            fcppt::tuple::object<
                fcppt::reference<fcppt::reference<libftl::impl::xml::node const> const>,
                fcppt::iterator::range<std::vector<fcppt::reference<
                    libftl::impl::xml::node const>>::const_iterator>> const &_split)
        {
          return fcppt::range::empty(fcppt::tuple::get<1U>(_split))
                     ? fcppt::deref(this->parser_).parse(fcppt::tuple::get<0U>(_split).get().get())
                     : fcppt::either::make_failure<result_type>(
                     // TODO(philipp): Put the excess nodes in the error?
                           libftl::xml::type_error{libftl::xml::type_error::variant{
                               libftl::xml::errors::excess_nodes{this->name_}}});
        });
  }
private:
  std::string name_;
  Parser parser_;
};

}

#endif
