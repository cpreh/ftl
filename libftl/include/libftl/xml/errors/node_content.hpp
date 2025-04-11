#ifndef LIBFTL_XML_ERRORS_NODE_CONTENT_HPP_INCLUDED
#define LIBFTL_XML_ERRORS_NODE_CONTENT_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/xml/type_error_fwd.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/parse/location.hpp>

namespace libftl::xml::errors
{
struct node_content
{
  LIBFTL_DETAIL_SYMBOL
  node_content(fcppt::optional::object<fcppt::parse::location>, libftl::xml::type_error &&);

  fcppt::optional::object<fcppt::parse::location> location_;

  fcppt::recursive<libftl::xml::type_error> error_;

  [[nodiscard]]
  bool operator==(node_content const &) const;
};
}

#endif
