#ifndef LIBFTL_SHIP_RESOURCES_HPP_INCLUDED
#define LIBFTL_SHIP_RESOURCES_HPP_INCLUDED

#include <libftl/detail/symbol.hpp>
#include <libftl/ship/resources_fwd.hpp>
#include <libftl/ship/images/object.hpp>
#include <libftl/ship/layout/object.hpp>
#include <libftl/xml/ship/result.hpp>
#include <fcppt/noncopyable.hpp>

namespace libftl::ship
{
class resources
{
  FCPPT_NONCOPYABLE(resources);

public:
  resources(
      libftl::xml::ship::result &&,
      libftl::ship::images::object &&,
      libftl::ship::layout::object &&);

  LIBFTL_DETAIL_SYMBOL
  resources(resources &&) noexcept;

  LIBFTL_DETAIL_SYMBOL
  resources &operator=(resources &&) noexcept;

  LIBFTL_DETAIL_SYMBOL
  ~resources();

  libftl::xml::ship::result ship_;

  libftl::ship::images::object images_;

  libftl::ship::layout::object layout_;
};

}

#endif
