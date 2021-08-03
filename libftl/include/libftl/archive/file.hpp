#ifndef LIBFTL_ARCHIVE_FILE_HPP_INCLUDED
#define LIBFTL_ARCHIVE_FILE_HPP_INCLUDED

#include <libftl/archive/entry.hpp>
#include <libftl/archive/file_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace archive
{
struct file
{
  using istream_ref = fcppt::reference<std::istream>;

  file(istream_ref const _stream, libftl::archive::entry const _entry)
      : stream_{_stream}, entry_{_entry}
  {
  }

  istream_ref stream_;

  libftl::archive::entry entry_;
};

}
}

#endif
