#include <libftl/archive/base.hpp>
#include <libftl/archive/open_path_error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/ship/layout/load.hpp>
#include <libftl/ship/layout/load_error.hpp>
#include <libftl/ship/layout/name.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/ship/layout/parse.hpp>
#include <libftl/ship/layout/parse_error.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::ship::layout::load_error, libftl::ship::layout::object>
libftl::ship::layout::load(
    libftl::archive::base const &_archive, libftl::ship::layout::name const &_name)
{
  return fcppt::either::bind(
      fcppt::either::map_failure(
          _archive.open(libftl::archive::path{"data"} / (_name.get() + ".txt")),
          [](libftl::archive::open_path_error &&_error)
          {
            return libftl::ship::layout::load_error{
                libftl::ship::layout::load_error::variant{std::move(_error)}};
          }),
      // NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
      [](fcppt::unique_ptr<std::istream> &&_stream)
      {
        return fcppt::either::map_failure(
            libftl::ship::layout::parse(*_stream),
            [](libftl::ship::layout::parse_error &&_error)
            {
              return libftl::ship::layout::load_error{
                  libftl::ship::layout::load_error::variant{std::move(_error)}};
            });
      });
}
