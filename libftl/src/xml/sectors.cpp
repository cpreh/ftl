#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/sectors.hpp>
#include <libftl/xml/generated/sectors.hpp>


libftl::xml::result<
	libftl::xml::generated::sectors::sectors_root
>
libftl::xml::sectors(
	std::istream &_input
)
{
	return
		libftl::impl::xml::read(
			_input,
			LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(
				sectors
			)
		);
}
