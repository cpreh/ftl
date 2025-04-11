#ifndef LIBFTL_ARCHIVE_OPEN_PATH_ERROR_HPP_INCLUDED
#define LIBFTL_ARCHIVE_OPEN_PATH_ERROR_HPP_INCLUDED

#include <libftl/archive/open_path_error_fwd.hpp> // IWYU pragma: export
#include <libftl/archive/path.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/recursive_impl.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace libftl::archive
{

struct open_path_error
{
  FCPPT_DECLARE_STRONG_TYPEDEF(std::filesystem::path, failed_to_open);

  struct missing_path
  {
    libftl::archive::path archive_path_;
    std::filesystem::path file_path_;
  };

  struct read_error
  {
    libftl::archive::path archive_path_;
    std::filesystem::path file_path_;
  };

  struct chain
  {
    chain(open_path_error &&, open_path_error &&);
    fcppt::recursive<open_path_error> error1_;
    fcppt::recursive<open_path_error> error2_;
  };

  using variant = fcppt::variant::object<failed_to_open, missing_path, read_error, chain>;

  variant value_;
};

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::archive::open_path_error const &);
}

#endif
