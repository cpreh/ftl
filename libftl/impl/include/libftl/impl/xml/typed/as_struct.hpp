#ifndef LIBFTL_IMPL_XML_TYPED_AS_STRUCT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_AS_STRUCT_HPP_INCLUDED

#include <libftl/impl/xml/typed/arg_type.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/type_error.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/tuple/as_struct.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template<typename Result, typename Parser>
// TODO(philipp): Concepts
class as_struct
{
public:
  using result_type = Result;
  using arg_type = libftl::impl::xml::typed::arg_type<Parser>;

  explicit as_struct(Parser &&_parser) : parser_{std::move(_parser)} {}

  [[nodiscard]] fcppt::either::object<libftl::xml::type_error, result_type>
  parse(arg_type const &_arg) const
  {
    return fcppt::either::map(
        fcppt::deref(this->parser_).parse(_arg),
        [](libftl::impl::xml::typed::result_type<Parser> &&_result)
        { return fcppt::tuple::as_struct<Result>(std::move(_result)); });
  }
private:
  Parser parser_;
};
}

#endif
