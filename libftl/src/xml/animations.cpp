#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/animations.hpp>
#include <libftl/xml/generated/animations.hpp>


libftl::xml::result<
	libftl::xml::generated::animations::animations_root
>
libftl::xml::animations(
	std::istream &_input
)
{
	return
		libftl::impl::xml::read(
			_input,
			LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(
				animations
			)
		);
}
