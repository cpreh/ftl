#ifndef LIBFTL_IMPL_ARCHIVE_CHAIN_HPP_INCLUDED
#define LIBFTL_IMPL_ARCHIVE_CHAIN_HPP_INCLUDED

#include <libftl/error_fwd.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl
{
namespace impl
{
namespace archive
{
class chain : public libftl::archive::base
{
  FCPPT_NONMOVABLE(chain);

public:
  chain(libftl::archive::base_unique_ptr &&, libftl::archive::base_unique_ptr &&);

  ~chain() override;

  [[nodiscard]] fcppt::either::object<libftl::error, fcppt::unique_ptr<std::istream>>
  open(libftl::archive::path const &) override;

private:
  libftl::archive::base_unique_ptr const archive1_;

  libftl::archive::base_unique_ptr const archive2_;
};

}
}
}

#endif
