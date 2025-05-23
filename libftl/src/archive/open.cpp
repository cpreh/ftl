#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/index.hpp>
#include <libftl/archive/index_error.hpp>
#include <libftl/archive/open.hpp>
#include <libftl/archive/open_error.hpp>
#include <libftl/archive/read_index.hpp>
#include <libftl/impl/archive/native.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/filesystem/open.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::archive::open_error, libftl::archive::base_unique_ptr>
libftl::archive::open(std::filesystem::path &&_path)
{
  return fcppt::either::bind(
      fcppt::either::from_optional(
          fcppt::filesystem::open<std::ifstream>(_path, std::ios_base::binary),
          [&_path]
          {
            return libftl::archive::open_error{
                .path_ = fcppt::copy(_path),
                .value_ = libftl::archive::open_error::variant{
                    libftl::archive::open_error::failed_to_open{}}};
          }),
      [&_path](
          std::ifstream &&_stream) // NOLINT(cppcoreguidelines-rvalue-reference-param-not-moved)
      {
        return fcppt::either::map(
            fcppt::either::map_failure(
                libftl::archive::read_index(_stream),
                [&_path](libftl::archive::index_error const _error)
                {
                  return libftl::archive::open_error{
                      .path_ = fcppt::copy(_path),
                      .value_ = libftl::archive::open_error::variant{_error}};
                }),
            [&_path](libftl::archive::index &&_index) -> libftl::archive::base_unique_ptr
            {
              return fcppt::unique_ptr_to_base<libftl::archive::base>(
                  fcppt::make_unique_ptr<libftl::impl::archive::native>(
                      std::move(_path), std::move(_index)));
            });
      });
}
