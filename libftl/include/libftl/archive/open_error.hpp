#ifndef LIBFTL_ARCHIVE_OPEN_ERROR_HPP_INCLUDED
#define LIBFTL_ARCHIVE_OPEN_ERROR_HPP_INCLUDED

#include <libftl/archive/index_error.hpp>
#include <libftl/archive/open_error_fwd.hpp> // IWYU pragma: export
#include <libftl/detail/symbol.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace libftl::archive
{
struct open_error
{
  struct failed_to_open {};
  using variant = fcppt::variant::object<failed_to_open, libftl::archive::index_error>;

  std::filesystem::path path_;
  variant value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::archive::open_error const &);
}

#endif
