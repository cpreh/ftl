#ifndef LIBFTL_IMPL_XML_LOAD_HPP_INCLUDED
#define LIBFTL_IMPL_XML_LOAD_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/impl/xml/document.hpp>
#include <libftl/impl/xml/parse.hpp>
#include <libftl/impl/xml/typed/arg_type.hpp>
#include <libftl/impl/xml/typed/result_type.hpp>
#include <fcppt/deref.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace libftl::impl::xml
{
template <typename Parser>
requires(std::is_same_v<libftl::impl::xml::typed::arg_type<Parser>, libftl::impl::xml::node_vector>)
[[nodiscard]] fcppt::either::object<libftl::error, libftl::impl::xml::typed::result_type<Parser>>
load(std::istream &_input, Parser const &_parser)
{
  return fcppt::either::bind(
      libftl::impl::xml::parse(_input),
      [&_parser](libftl::impl::xml::document const &_doc)
      { return fcppt::deref(_parser).parse(_doc.nodes_); });
}
}

#endif
