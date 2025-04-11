#ifndef LIBFTL_ARCHIVE_ENTRY_HPP_INCLUDED
#define LIBFTL_ARCHIVE_ENTRY_HPP_INCLUDED

#include <libftl/archive/entry_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>

namespace libftl::archive
{
struct entry
{
  std::streamsize offset_;

  std::streamsize length_;
};

}

#endif
