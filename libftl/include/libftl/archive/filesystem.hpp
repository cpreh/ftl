#ifndef LIBFTL_ARCHIVE_FILESYSTEM_HPP_INCLUDED
#define LIBFTL_ARCHIVE_FILESYSTEM_HPP_INCLUDED

#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace libftl::archive
{
LIBFTL_DETAIL_SYMBOL
libftl::archive::base_unique_ptr filesystem(std::filesystem::path &&);

}

#endif
