#include <libftl/error.hpp>
#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/sectors/load.hpp>
#include <libftl/xml/generated/sectors.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

fcppt::either::
    object<libftl::error, fcppt::unique_ptr<libftl::xml::generated::sectors::sectors_root>>
    libftl::xml::sectors::load(std::istream &_input)
{
  return libftl::impl::xml::read(_input, LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(sectors));
}
