#include <libftl/archive/base.hpp> // IWYU pragma: export
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/chain.hpp>
#include <libftl/archive/filesystem.hpp>
#include <libftl/archive/open.hpp>
#include <libftl/archive/open_error.hpp>
#include <libftl/options/data_file_label.hpp>
#include <libftl/options/native_resource_record.hpp>
#include <libftl/options/open_archive.hpp>
#include <libftl/options/resource_file_label.hpp>
#include <libftl/options/resource_path_label.hpp>
#include <libftl/options/resource_variant.hpp>
#include <libftl/options/unpacked_resource_record.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/options/left.hpp>
#include <fcppt/options/right.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

fcppt::either::object<libftl::archive::open_error, libftl::archive::base_unique_ptr>
libftl::options::open_archive(libftl::options::resource_variant const &_args)
{
  return fcppt::variant::match(
      _args,
      [](fcppt::options::left<libftl::options::native_resource_record> const &_native)
      {
        return fcppt::either::apply(
            [](libftl::archive::base_unique_ptr &&_archive1,
               libftl::archive::base_unique_ptr &&_archive2)
            { return libftl::archive::chain(std::move(_archive1), std::move(_archive2)); },
            libftl::archive::open(std::filesystem::path{
                fcppt::record::get<libftl::options::data_file_label>(_native.get())}),
            libftl::archive::open(std::filesystem::path{
                fcppt::record::get<libftl::options::resource_file_label>(_native.get())}));
      },
      [](fcppt::options::right<libftl::options::unpacked_resource_record> const &_unpacked)
      {
        return fcppt::either::make_success<libftl::archive::open_error>(
            libftl::archive::filesystem(std::filesystem::path{
                fcppt::record::get<libftl::options::resource_path_label>(_unpacked.get())}));
      });
}
