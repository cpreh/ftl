#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <libftl/impl/archive/chain.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::impl::archive::chain::chain(
    libftl::archive::base_unique_ptr &&_archive1, libftl::archive::base_unique_ptr &&_archive2)
    : libftl::archive::base{}, archive1_{std::move(_archive1)}, archive2_{std::move(_archive2)}
{
}

libftl::impl::archive::chain::~chain() = default;

fcppt::either::object<libftl::error, fcppt::unique_ptr<std::istream>>
libftl::impl::archive::chain::open(libftl::archive::path const &_path)
{
  return fcppt::either::match(
      this->archive1_->open(_path),
      [&_path, this](libftl::error &&_error1)
      {
        return fcppt::either::map_failure(
            this->archive2_->open(_path),
            [&_error1](libftl::error &&_error2) {
              return libftl::error{
                  std::move(_error1.get()) + FCPPT_TEXT('\n') + std::move(_error2.get())};
            });
      },
      [](fcppt::unique_ptr<std::istream> &&_result)
      { return fcppt::either::make_success<libftl::error>(std::move(_result)); });
}
