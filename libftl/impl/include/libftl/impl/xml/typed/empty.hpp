#ifndef LIBFTL_IMPL_XML_TYPED_EMPTY_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_EMPTY_HPP_INCLUDED

#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/not_empty.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>

namespace libftl::impl::xml::typed
{
struct empty
{
  using result_type = fcppt::unit;

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(fcppt::optional::object<libftl::impl::xml::inner_node> const &_node) const // NOLINT(readability-convert-member-functions-to-static)
  {
    return fcppt::optional::maybe(
        _node,
        [] { return fcppt::either::make_success<libftl::xml::type_error>(fcppt::unit{}); },
        [](libftl::impl::xml::inner_node const &)
        {
          return fcppt::either::make_failure<result_type>(libftl::xml::type_error{
              libftl::xml::type_error::variant{libftl::xml::errors::not_empty{}}});
        });
  }
};
}

#endif
