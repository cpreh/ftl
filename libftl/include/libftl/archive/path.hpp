#ifndef LIBFTL_ARCHIVE_PATH_HPP_INCLUDED
#define LIBFTL_ARCHIVE_PATH_HPP_INCLUDED

#include <libftl/archive/path_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/no_init_fwd.hpp>
#include <fcppt/io/istream_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace libftl::archive
{
class path
{
public:
  LIBFTL_DETAIL_SYMBOL
  explicit path(fcppt::no_init const &);

  LIBFTL_DETAIL_SYMBOL
  explicit path(std::string &&);

  [[nodiscard]] LIBFTL_DETAIL_SYMBOL std::string const &rep() const;

  LIBFTL_DETAIL_SYMBOL
  void add(std::string &&);

  LIBFTL_DETAIL_SYMBOL
  path &operator+=(path &&);

private:
  std::string rep_;
};

LIBFTL_DETAIL_SYMBOL
libftl::archive::path operator+(libftl::archive::path &&, libftl::archive::path &&);

LIBFTL_DETAIL_SYMBOL
libftl::archive::path operator/(libftl::archive::path &&, std::string &&);

LIBFTL_DETAIL_SYMBOL
fcppt::io::istream &operator>>(fcppt::io::istream &, libftl::archive::path &);

LIBFTL_DETAIL_SYMBOL
fcppt::io::ostream &operator<<(fcppt::io::ostream &, libftl::archive::path const &);

}

#endif
