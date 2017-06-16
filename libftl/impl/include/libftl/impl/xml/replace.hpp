#ifndef LIBFTL_IMPL_XML_REPLACE_HPP_INCLUDED
#define LIBFTL_IMPL_XML_REPLACE_HPP_INCLUDED

#include <libftl/impl/xml/replace_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <regex>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace impl
{
namespace xml
{

struct replace
{
	std::regex regex_;

	std::string replace_string_;
};

}
}
}

#endif
