#include <libftl/archive/path.hpp>
#include <fcppt/no_init_fwd.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/io/extract.hpp>
#include <fcppt/io/istream.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::archive::path::path(fcppt::no_init const &) : rep_{} {}

libftl::archive::path::path(std::string &&_rep) : rep_{std::move(_rep)} {}

std::string const &libftl::archive::path::rep() const { return rep_; }

void libftl::archive::path::add(std::string &&_name) { rep_ += "/" + std::move(_name); }

// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
libftl::archive::path &libftl::archive::path::operator+=(path &&_other)
{
  rep_ = std::move(rep_) + "/" + std::move(_other.rep_);

  return *this;
}

libftl::archive::path
// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
libftl::archive::operator+(libftl::archive::path &&_path1, libftl::archive::path &&_path2)
{
  return _path1 += std::move(_path2);
}

libftl::archive::path libftl::archive::operator/(libftl::archive::path &&_path, std::string &&_name)
{
  _path.add(std::move(_name));

  return std::move(_path);
}

fcppt::io::istream &
libftl::archive::operator>>(fcppt::io::istream &_stream, libftl::archive::path &_path)
{
  fcppt::optional::maybe_void(
      fcppt::io::extract<fcppt::string>(_stream),
      [&_stream, &_path](fcppt::string &&_value)
      {
        fcppt::optional::maybe(
            fcppt::to_std_string(std::move(_value)),
            [&_stream] { _stream.setstate(std::ios_base::failbit); },
            [&_path](std::string &&_string) { _path = libftl::archive::path{std::move(_string)}; });
      });

  return _stream;
}

fcppt::io::ostream &
libftl::archive::operator<<(fcppt::io::ostream &_stream, libftl::archive::path const &_path)
{
  return _stream << fcppt::from_std_string(_path.rep());
}
