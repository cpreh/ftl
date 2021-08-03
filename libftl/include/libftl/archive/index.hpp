#ifndef LIBFTL_ARCHIVE_INDEX_HPP_INCLUDED
#define LIBFTL_ARCHIVE_INDEX_HPP_INCLUDED

#include <libftl/archive/entry.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace archive
{
using index = std::unordered_map<std::string, libftl::archive::entry>;

}
}

#endif
