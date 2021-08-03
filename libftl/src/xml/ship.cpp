#include <libftl/error.hpp>
#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/ship.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/object_impl.hpp>

fcppt::either::object<libftl::error, fcppt::unique_ptr<libftl::xml::generated::ship::ship_root>>
libftl::xml::ship(std::istream &_input)
{
  return libftl::impl::xml::read(_input, LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(ship));
}
