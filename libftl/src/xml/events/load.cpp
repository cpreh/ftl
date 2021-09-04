#include <libftl/error.hpp>
#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/events/load.hpp>
#include <libftl/xml/generated/events.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/object_impl.hpp>

fcppt::either::object<libftl::error, fcppt::unique_ptr<libftl::xml::generated::events::events_root>>
libftl::xml::events::load(std::istream &_input)
{
  return libftl::impl::xml::read(_input, LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(events));
}
