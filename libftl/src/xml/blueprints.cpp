#include <libftl/impl/xml/make_load_function.hpp>
#include <libftl/impl/xml/read.hpp>
#include <libftl/xml/result.hpp>
#include <libftl/xml/blueprints.hpp>
#include <libftl/xml/generated/blueprints.hpp>


libftl::xml::result<
	libftl::xml::generated::blueprints::blueprints_root
>
libftl::xml::blueprints(
	std::istream &_input
)
{
	return
		libftl::impl::xml::read(
			_input,
			LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(
				blueprints
			)
		);
}
