#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/ship.hpp>
#include <libftl/xml/generated/ship.hpp>


libftl::xml::result<
	libftl::xml::generated::ship::ship_root
>
libftl::xml::ship(
	std::istream &_input
)
{
	return
		libftl::impl::xml::read(
			_input,
			LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(
				ship
			)
		);
}
