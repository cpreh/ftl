#ifndef LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION_HPP_INCLUDED
#define LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION_HPP_INCLUDED

#include <libftl/impl/xml/load_function.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <istream>
#include <fcppt/config/external_end.hpp>


#define LIBFTL_IMPL_XML_MAKE_LOAD_FUNCTION(\
	name\
)\
libftl::impl::xml::load_function<\
	libftl::xml::generated:: name ::name ## _root\
>{\
	[](\
		std::istream &_stream\
	)\
	->\
	std::unique_ptr<\
		libftl::xml::generated:: name ::name ## _root\
	>\
	{\
		return\
			libftl::xml::generated:: name ::root(\
				_stream,\
				xml_schema::flags::dont_validate\
			);\
	}\
}

#endif
