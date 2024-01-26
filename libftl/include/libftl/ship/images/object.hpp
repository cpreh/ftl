#ifndef LIBFTL_SHIP_IMAGES_OBJECT_HPP_INCLUDED
#define LIBFTL_SHIP_IMAGES_OBJECT_HPP_INCLUDED

#include <libftl/ship/images/object_fwd.hpp> // IWYU pragma: keep
#include <libftl/xml/ship/gib.hpp>
#include <libftl/xml/ship/offset.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace libftl::ship::images
{
struct object
{
  FCPPT_DECLARE_STRONG_TYPEDEF(sge::texture::const_part_shared_ptr, base);

  FCPPT_DECLARE_STRONG_TYPEDEF(sge::texture::const_part_shared_ptr, shield);

  struct offset_image
  {
    offset_image(libftl::xml::ship::offset, sge::texture::const_part_shared_ptr &&);

    libftl::xml::ship::offset offset_;

    sge::texture::const_part_shared_ptr image_;
  };

  FCPPT_DECLARE_STRONG_TYPEDEF(offset_image, floor);

  FCPPT_DECLARE_STRONG_TYPEDEF(offset_image, cloak);

  struct gib_image
  {
    gib_image(libftl::xml::ship::gib, sge::texture::const_part_shared_ptr &&);

    libftl::xml::ship::gib gib_;

    sge::texture::const_part_shared_ptr image_;
  };

  object(
      base &&,
      fcppt::optional::object<shield> &&,
      fcppt::optional::object<floor> &&,
      fcppt::optional::object<cloak> &&,
      std::vector<gib_image> &&);

  base base_;

  fcppt::optional::object<shield> shield_;

  fcppt::optional::object<floor> floor_;

  fcppt::optional::object<cloak> cloak_;

  std::vector<gib_image> gibs_;
};

}

#endif
