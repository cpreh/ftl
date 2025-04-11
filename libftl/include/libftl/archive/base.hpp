#ifndef LIBFTL_ARCHIVE_BASE_HPP_INCLUDED
#define LIBFTL_ARCHIVE_BASE_HPP_INCLUDED

#include <libftl/archive/base_fwd.hpp>
#include <libftl/archive/open_path_error_fwd.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace libftl::archive
{
class base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  LIBFTL_DETAIL_SYMBOL
  virtual ~base();

  [[nodiscard]] virtual fcppt::either::
      object<libftl::archive::open_path_error, fcppt::unique_ptr<std::istream>>
      open(libftl::archive::path const &) const = 0;
};

}

#endif
