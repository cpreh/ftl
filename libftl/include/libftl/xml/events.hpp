#ifndef LIBFTL_XML_EVENTS_HPP_INCLUDED
#define LIBFTL_XML_EVENTS_HPP_INCLUDED

#include <libftl/error.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/xml/generated/events.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace xml
{
LIBFTL_DETAIL_SYMBOL
fcppt::either::object<libftl::error, fcppt::unique_ptr<libftl::xml::generated::events::events_root>>
events(std::istream &);

}
}

#endif
