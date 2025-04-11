#ifndef LIBFTL_SPRITE_IMAGES_HPP_INCLUDED
#define LIBFTL_SPRITE_IMAGES_HPP_INCLUDED

#include <libftl/archive/base_ref.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/sprite/load_error_fwd.hpp>
#include <libftl/sprite/images_fwd.hpp> // IWYU pragma: keep
#include <sge/image2d/system_ref.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>

namespace libftl::sprite
{
class images
{
  FCPPT_NONCOPYABLE(images);

public:
  LIBFTL_DETAIL_SYMBOL
  images(sge::renderer::device::core_ref, sge::image2d::system_ref, libftl::archive::base_ref);

  LIBFTL_DETAIL_SYMBOL
  images(images &&) noexcept;

  LIBFTL_DETAIL_SYMBOL
  images &operator=(images &&) noexcept;

  LIBFTL_DETAIL_SYMBOL
  ~images();

  LIBFTL_DETAIL_SYMBOL
  sge::texture::const_part_shared_ptr opaque() const;

  LIBFTL_DETAIL_SYMBOL
  fcppt::either::object<libftl::sprite::load_error, sge::texture::const_part_shared_ptr>
  load(libftl::archive::path const &) const;

private:
  sge::renderer::device::core_ref renderer_device_;

  sge::image2d::system_ref image_system_;

  libftl::archive::base_ref archive_;

  sge::texture::const_part_shared_ptr opaque_;

  mutable std::unordered_map<std::string, sge::texture::const_part_shared_ptr> impl_;
};

}

#endif
