#ifndef LIBFTL_IMPL_XML_TYPED_ALTERNATIVE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_ALTERNATIVE_HPP_INCLUDED

#include <libftl/impl/xml/node_fwd.hpp>
#include <libftl/impl/xml/typed/parses.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/alternative.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/function.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/array/init.hpp>
#include <fcppt/array/object.hpp>
#include <fcppt/either/first_success.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/tuple/element.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <type_traits>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename... Parsers>
requires (libftl::impl::xml::typed::parses<Parsers, libftl::impl::xml::node> &&...)
class alternative
{
public:
  using result_type = fcppt::variant::object<libftl::impl::xml::typed::result_type<Parsers>...>;
  using arg_type = libftl::impl::xml::node;

  explicit alternative(Parsers &&..._parsers) : parsers_{std::move(_parsers)...} {}

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    using inner_function =
        fcppt::function<fcppt::either::object<libftl::xml::type_error, result_type>()>;

    return fcppt::either::map_failure(
        fcppt::either::first_success(
            fcppt::array::init<fcppt::array::object<inner_function, sizeof...(Parsers)>>(
                [this, &_node]<std::size_t Index>(std::integral_constant<std::size_t, Index>)
                {
                  return inner_function{
                      [this, &_node]
                      {
                        return fcppt::either::map(
                            fcppt::deref(fcppt::tuple::get<Index>(this->parsers_)).parse(_node),
                            [](libftl::impl::xml::typed::result_type<
                                fcppt::tuple::element<Index, decltype(parsers_)>> &&_inner)
                            { return result_type{std::move(_inner)}; });
                      }};
                })),
        [](std::vector<libftl::xml::type_error> &&_errors) -> libftl::xml::type_error
        {
          return libftl::xml::type_error{
              libftl::xml::type_error::variant{libftl::xml::errors::alternative{
                  fcppt::algorithm::map<std::vector<fcppt::recursive<libftl::xml::type_error>>>(
                      std::move(_errors),
                      [](libftl::xml::type_error &&_error)
                      { return fcppt::make_recursive(std::move(_error)); })}}};
        });
  }
private:
  fcppt::tuple::object<Parsers...> parsers_;
};

template<typename Parser1, typename Parser2, typename... Parsers>
alternative(Parser1 &&, Parser2 &&, Parsers &&...) -> alternative<Parser1, Parser2, Parsers...>;

}

#endif
