#ifndef LIBFTL_IMPL_XML_FILE_TO_STRING_HPP_INCLUDED
#define LIBFTL_IMPL_XML_FILE_TO_STRING_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace impl
{
namespace xml
{
std::string file_to_string(std::istream &);

}
}
}

#endif
