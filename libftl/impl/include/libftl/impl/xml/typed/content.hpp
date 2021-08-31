#ifndef LIBFTL_IMPL_XML_TYPED_CONTENT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_CONTENT_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/inner_node.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/type_name_from_info.hpp>
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
#include <typeinfo>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template <typename Result>
struct content
{
  using result_type = Result;

  [[nodiscard]] fcppt::either::object<libftl::error, Result>
  parse(fcppt::optional::object<libftl::impl::xml::inner_node> const &_node) const
  {
    return fcppt::optional::maybe(
        _node,
        []
        {
          return fcppt::either::make_failure<Result>(libftl::error{
              fcppt::string{FCPPT_TEXT("Expected node type ")} +
              fcppt::from_std_string(fcppt::type_name_from_info(typeid(Result))) +
              FCPPT_TEXT(" but node is empty.")});
        },
        [](libftl::impl::xml::inner_node const &_inner)
        {
          return fcppt::variant::match(
              _inner.content_,
              [](libftl::impl::xml::node_vector const &)
              {
                return fcppt::either::make_failure<Result>(libftl::error{
                    fcppt::string{FCPPT_TEXT("Expected node type ")} +
                    fcppt::from_std_string(fcppt::type_name_from_info(typeid(Result))) +
                    FCPPT_TEXT(" but node is an inner node.")});
              },
              [](std::string const &_content)
              {
                if constexpr (std::is_same_v<Result, std::string>)
                {
                  return fcppt::either::make_success<libftl::error>(_content);
                }
                else
                {
                  return fcppt::either::from_optional(
                      fcppt::extract_from_string<Result>(_content),
                      [&_content]
                      {
                        return libftl::error{
                            fcppt::string{FCPPT_TEXT("Failed to convert \"")} +
                            fcppt::from_std_string(_content) + FCPPT_TEXT(" to type ") +
                            fcppt::from_std_string(fcppt::type_name_from_info(typeid(Result))) +
                            FCPPT_TEXT(".")};
                      });
                }
              });
        });
  }
};
}

#endif
