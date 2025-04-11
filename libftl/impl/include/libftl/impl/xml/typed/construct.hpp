#ifndef LIBFTL_IMPL_XML_TYPED_CONSTRUCT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_CONSTRUCT_HPP_INCLUDED

#include <libftl/impl/xml/typed/arg_type.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/type_error.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template<typename Result, typename Parser>
// TODO(philipp): This leads to a terrible error message.
//requires (std::is_constructible_v<Result,libftl::impl::xml::typed::result_type<Parser>>)
class construct
{
public:
  using result_type = Result;
  using arg_type = libftl::impl::xml::typed::arg_type<Parser>;

  explicit construct(Parser &&_parser) : parser_{std::move(_parser)} {}

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(arg_type const &_arg) const
  {
    return fcppt::either::map(
        fcppt::deref(this->parser_).parse(_arg),
        [](libftl::impl::xml::typed::result_type<Parser> &&_result)
        { return Result{std::move(_result)}; });
  }
private:
  Parser parser_;
};
}

#endif
