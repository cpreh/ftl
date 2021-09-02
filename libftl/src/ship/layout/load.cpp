#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/ship/layout/load.hpp>
#include <libftl/ship/layout/name.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/parse.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::error, libftl::ship::layout::object> libftl::ship::layout::load(
    libftl::archive::base const &_archive, libftl::ship::layout::name const &_name)
{
  return fcppt::either::bind(
      _archive.open(libftl::archive::path{"data"} / (_name.get() + ".txt")),
      [](fcppt::unique_ptr<std::istream> &&_stream)
      { return libftl::ship::layout::parse(*_stream); });
}
