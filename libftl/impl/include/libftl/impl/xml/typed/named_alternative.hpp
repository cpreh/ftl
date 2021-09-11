#ifndef LIBFTL_IMPL_XML_TYPED_NAMED_ALTERNATIVE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_NAMED_ALTERNATIVE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/location_to_string.hpp>
#include <libftl/impl/xml/node_fwd.hpp>
#include <libftl/impl/xml/typed/is_named_node.hpp>
#include <libftl/impl/xml/typed/is_named_node_base.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/deref_type.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/loop_break_tuple.hpp>
#include <fcppt/either/first_success.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename... Parsers>
class named_alternative
{
public:
  template <typename Type>
  using is_valid_member = std::disjunction<
      libftl::impl::xml::typed::is_named_node<Type>,
      libftl::impl::xml::typed::is_named_node_base<Type>>;

  static_assert(fcppt::mpl::list::all_of<
                fcppt::mpl::list::object<Parsers...>,
                fcppt::mpl::bind<
                    fcppt::mpl::lambda<named_alternative::is_valid_member>,
                    fcppt::mpl::bind<
                        fcppt::mpl::lambda<std::remove_cvref_t>,
                        fcppt::mpl::lambda<fcppt::deref_type>>>>::value);

  using result_type = fcppt::variant::object<libftl::impl::xml::typed::result_type<Parsers>...>;
  using arg_type = libftl::impl::xml::node;

  explicit named_alternative(Parsers &&..._parsers) : parsers_{std::move(_parsers)...} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    return fcppt::algorithm::fold(
        this->parsers_,
        fcppt::either::object<libftl::error, result_type>{libftl::error{
            libftl::impl::xml::location_to_string(_node.location_) +
            fcppt::string{FCPPT_TEXT("Invalid node \"")} +
            fcppt::from_std_string(_node.opening_tag_) + FCPPT_TEXT("\".")}},
        [&_node](auto const &_parser, fcppt::either::object<libftl::error, result_type> &&_state)
        {
          return _state.has_success() || fcppt::deref(_parser).name() != _node.opening_tag_
                     ? std::move(_state)
                     : fcppt::either::map(
                           fcppt::deref(_parser).parse(_node),
                           [](libftl::impl::xml::typed::result_type<decltype(_parser)> &&_result)
                           { return result_type{std::move(_result)}; });
        });
  }

private:
  fcppt::tuple::object<Parsers...> parsers_;
};

template<typename Parser1, typename Parser2, typename... Parsers>
named_alternative(Parser1 &&, Parser2 &&, Parsers &&...) -> named_alternative<Parser1, Parser2, Parsers...>;

}

#endif
