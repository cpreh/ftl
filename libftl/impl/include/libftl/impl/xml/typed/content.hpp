#ifndef LIBFTL_IMPL_XML_TYPED_CONTENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_CONTENT_HPP_INCLUDED

#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node.hpp> // IWYU pragma: keep
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/xml/type_error.hpp>
#include <libftl/xml/errors/content_conversion.hpp>
#include <libftl/xml/errors/content_empty.hpp>
#include <libftl/xml/errors/content_inner.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <type_traits>
#include <typeinfo> // IWYU pragma: keep
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Result>
struct content
{
  using result_type = Result;

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, Result>
  parse(fcppt::optional::object<libftl::impl::xml::inner_node> const &_node) const
  {
    return fcppt::optional::maybe(
        _node,
        []
        {
          return fcppt::either::make_failure<Result>(
              libftl::xml::type_error{libftl::xml::type_error::variant{
                  libftl::xml::errors::content_empty{typeid(Result)}}});
        },
        [](libftl::impl::xml::inner_node const &_inner)
        {
          return fcppt::variant::match(
              _inner.content_,
              [](libftl::impl::xml::node_vector const &)
              {
                return fcppt::either::make_failure<Result>(
                    libftl::xml::type_error{libftl::xml::type_error::variant{
                        libftl::xml::errors::content_inner{typeid(Result)}}});
              },
              [](std::string const &_content)
              {
                if constexpr (std::is_same_v<Result, std::string>)
                {
                  return fcppt::either::make_success<libftl::xml::type_error>(_content);
                }
                else
                {
                  return fcppt::either::from_optional(
                      fcppt::extract_from_string<Result>(_content),
                      [&_content]
                      {
                        return libftl::xml::type_error{libftl::xml::type_error::variant{
                            libftl::xml::errors::content_conversion{
                                .type_ = typeid(Result), .content_ = _content}}};
                      });
                }
              });
        });
  }
};
}

#endif
