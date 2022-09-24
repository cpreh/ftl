#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/base_ref.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/sprite/images.hpp>
#include <sge/image/channel8.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/la8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/luminance.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/store/la8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/create_planar_from_file.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/texture/part_raw_ptr.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <istream>
#include <utility>
#include <fcppt/config/external_end.hpp>

libftl::sprite::images::images(
    sge::renderer::device::core_ref const _renderer_device,
    sge::image2d::system_ref const _image_system,
    libftl::archive::base_ref const _archive)
    : renderer_device_{_renderer_device},
      image_system_{_image_system},
      archive_{_archive},
      opaque_{
          [&_renderer_device]
          {
            using store = sge::image2d::store::la8;

            store const data{
                fcppt::math::dim::fill<sge::image2d::dim>(
                    32), // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                store::init_function{
                    [](store::view_type const &_view)
                    {
                      auto const channel(fcppt::literal<sge::image::channel8>(255));

                      sge::image2d::algorithm::fill(
                          sge::image2d::view::object{sge::image::view::wrap(_view)},
                          sge::image::color::any::object{sge::image::color::la8{
                              (sge::image::color::init::luminance() =
                                   channel)(sge::image::color::init::alpha() = channel)}},
                          sge::image::algorithm::uninitialized::yes);
                    }}};

            return fcppt::make_shared_ptr<sge::texture::part_raw_ptr>(
                sge::renderer::texture::create_planar_from_view(
                    _renderer_device,
                    sge::image2d::view::const_object{data.const_wrapped_view()},
                    sge::renderer::texture::mipmap::off(),
                    sge::renderer::resource_flags_field::null(),
                    sge::renderer::texture::emulate_srgb::no));
          }()},
      impl_{}
{
}

libftl::sprite::images::images(images &&) noexcept = default;

libftl::sprite::images &libftl::sprite::images::operator=(images &&) noexcept = default;

libftl::sprite::images::~images() = default;

sge::texture::const_part_shared_ptr libftl::sprite::images::opaque() const { return opaque_; }

fcppt::either::object<libftl::error, sge::texture::const_part_shared_ptr>
libftl::sprite::images::load(libftl::archive::path const &_path) const
{
  libftl::archive::path const full_path{
      (libftl::archive::path{"img"}) + libftl::archive::path{_path}};

  return fcppt::optional::maybe(
      fcppt::container::find_opt_mapped(impl_, full_path.rep()),
      [&full_path, this]
      {
        return fcppt::either::bind(
            archive_.get().open(full_path),
            [&full_path, this](fcppt::unique_ptr<std::istream> &&_stream)
            {
              return fcppt::variant::match(
                  image_system_.get().load_stream(
                      sge::media::stream_unique_ptr{std::move(_stream)},
                      sge::media::optional_extension{sge::media::extension{FCPPT_TEXT("png")}},
                      sge::media::optional_name{}),
                  [&full_path](sge::media::stream_unique_ptr &&)
                  {
                    return fcppt::either::make_failure<sge::texture::const_part_shared_ptr>(
                        libftl::error{
                            FCPPT_TEXT("Unable to load ") +
                            fcppt::from_std_string(full_path.rep())});
                  },
                  [&full_path, this](sge::image2d::file_unique_ptr &&_file)
                  {
                    sge::texture::const_part_shared_ptr const result{
                        fcppt::make_shared_ptr<sge::texture::part_raw_ptr>(
                            sge::renderer::texture::create_planar_from_file(
                                this->renderer_device_,
                                *_file,
                                sge::renderer::texture::mipmap::off(),
                                sge::renderer::resource_flags_field::null(),
                                sge::renderer::texture::emulate_srgb::yes))};

                    this->impl_.insert(std::make_pair(full_path.rep(), result));

                    return fcppt::either::make_success<libftl::error>(result);
                  });
            });
      },
      [](fcppt::reference<sge::texture::const_part_shared_ptr> const _ptr)
      { return fcppt::either::make_success<libftl::error>(_ptr.get()); });
}
