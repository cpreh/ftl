#ifndef LIBFTL_SPRITE_IMAGES_HPP_INCLUDED
#define LIBFTL_SPRITE_IMAGES_HPP_INCLUDED

#include <libftl/error_fwd.hpp>
#include <libftl/archive/base_fwd.hpp>
#include <libftl/archive/path_fwd.hpp>
#include <libftl/detail/symbol.hpp>
#include <libftl/sprite/images_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/either/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <unordered_map>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace sprite
{

class images
{
	FCPPT_NONCOPYABLE(
		images
	);
public:
	LIBFTL_DETAIL_SYMBOL
	images(
		fcppt::reference<
			sge::renderer::device::core
		>,
		fcppt::reference<
			sge::image2d::system
		>,
		fcppt::reference<
			libftl::archive::base
		>
	);

	LIBFTL_DETAIL_SYMBOL
	images(
		images &&
	);

	LIBFTL_DETAIL_SYMBOL
	images &
	operator=(
		images &&
	);

	LIBFTL_DETAIL_SYMBOL
	~images();

	LIBFTL_DETAIL_SYMBOL
	sge::texture::const_part_shared_ptr
	opaque() const;

	// TODO: Make this const
	LIBFTL_DETAIL_SYMBOL
	fcppt::either::object<
		libftl::error,
		sge::texture::const_part_shared_ptr
	>
	load(
		libftl::archive::path const &
	) const;
private:
	fcppt::reference<
		sge::renderer::device::core
	> renderer_device_;

	fcppt::reference<
		sge::image2d::system
	> image_system_;

	fcppt::reference<
		libftl::archive::base
	> archive_;

	sge::texture::const_part_shared_ptr opaque_;

	mutable
	std::unordered_map<
		std::string,
		sge::texture::const_part_shared_ptr
	>
	impl_;
};

}
}

#endif
