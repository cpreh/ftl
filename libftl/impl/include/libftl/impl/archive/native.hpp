#ifndef LIBFTL_IMPL_ARCHIVE_NATIVE_HPP_INCLUDED
#define LIBFTL_IMPL_ARCHIVE_NATIVE_HPP_INCLUDED

#include <libftl/error_fwd.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/index.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace impl
{
namespace archive
{
class native : public libftl::archive::base
{
  FCPPT_NONMOVABLE(native);

public:
  native(std::filesystem::path &&, libftl::archive::index &&);

  ~native() override;

  [[nodiscard]] fcppt::either::object<libftl::error, fcppt::unique_ptr<std::istream>>
  open(libftl::archive::path const &) const override;

private:
  std::filesystem::path const file_path_;

  libftl::archive::index const index_;
};

}
}
}

#endif
