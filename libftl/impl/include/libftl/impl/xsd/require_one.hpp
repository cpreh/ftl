#ifndef LIBFTL_IMPL_XSD_REQUIRE_ONE_HPP_INCLUDED
#define LIBFTL_IMPL_XSD_REQUIRE_ONE_HPP_INCLUDED

#include <libftl/error.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/tree/containers.hxx>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace impl
{
namespace xsd
{
template <typename Type>
fcppt::either::object<libftl::error, fcppt::reference<Type const>>
require_one(fcppt::string const &_name, ::xsd::cxx::tree::sequence<Type> const &_elements)
{
  return _elements.size() >= 2U
             ? fcppt::either::make_failure<fcppt::reference<Type const>>(
                   libftl::error{_name + FCPPT_TEXT(" specified multiple times.")})
             : fcppt::either::from_optional(
                   fcppt::container::maybe_front(_elements),
                   [&_name] { return libftl::error{FCPPT_TEXT("Missing element ") + _name}; });
}

}
}
}

#endif
