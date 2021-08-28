#ifndef LIBFTL_IMPL_XML_TYPED_CONSTRUCT_HPP_INCLUDED
#define LIBFTL_IMPL_XML_TYPED_CONSTRUCT_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/node.hpp>
#include <libftl/impl/xml/typed/parses.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml::typed
{
template<typename Result, typename Parser>
requires libftl::impl::xml::typed::parses<Parser, libftl::impl::xml::node>
class construct
{
public:
  using result_type = Result;

  explicit construct(Parser &&_parser) : parser_{std::move(_parser)} {}

  [[nodiscard]] fcppt::either::object<libftl::error, result_type>
  parse(libftl::impl::xml::node const &_node) const
  {
    return fcppt::either::map(
        fcppt::deref(this->parser_).parse(_node),
        [](libftl::impl::xml::typed::result_type<Parser> &&_result)
        { return Result{std::move(_result)}; });
  }
private:
  Parser parser_;
};
}

#endif
