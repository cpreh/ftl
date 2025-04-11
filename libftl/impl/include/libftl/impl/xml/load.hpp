#ifndef LIBFTL_IMPL_XML_LOAD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_LOAD_HPP_INCLUDED

#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/node_vector.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/typed/arg_type.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <libftl/xml/error.hpp>
#include <libftl/xml/type_error.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/parse/parse_stream_error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
template <typename Parser>
requires(std::is_same_v<libftl::impl::xml::typed::arg_type<Parser>, libftl::impl::xml::node_vector>)
[[nodiscard]] fcppt::either::object<libftl::xml::error, libftl::impl::xml::typed::result_type<Parser>>
load(std::istream &_input, Parser const &_parser)
{
  return fcppt::either::bind(
      fcppt::either::map_failure(
          libftl::impl::xml::parse(_input),
          [](fcppt::parse::parse_stream_error<char> &&_error)
          { return libftl::xml::error{libftl::xml::error::variant{std::move(_error)}}; }),
      [&_parser](libftl::impl::xml::document const &_doc)
      {
        return fcppt::either::map_failure(
            fcppt::deref(_parser).parse(_doc.nodes_),
            [](libftl::xml::type_error &&_error)
            { return libftl::xml::error{libftl::xml::error::variant{std::move(_error)}}; });
      });
}
}

#endif
