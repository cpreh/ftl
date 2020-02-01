#ifndef LIBFTL_SHIP_IMAGES_OBJECT_HPP_INCLUDED
#define LIBFTL_SHIP_IMAGES_OBJECT_HPP_INCLUDED

#include <libftl/ship/images/object_fwd.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace libftl
{
namespace ship
{
namespace images
{

struct object
{
	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::texture::const_part_shared_ptr,
		base
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		sge::texture::const_part_shared_ptr,
		shield
	);

	struct offset_image
	{
		offset_image(
			libftl::xml::generated::ship::offset,
			sge::texture::const_part_shared_ptr &&
		);

		libftl::xml::generated::ship::offset offset_;

		sge::texture::const_part_shared_ptr image_;
	};

	FCPPT_MAKE_STRONG_TYPEDEF(
		offset_image,
		floor
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		offset_image,
		cloak
	);

	struct gib_image
	{
		gib_image(
			libftl::xml::generated::ship::gib,
			sge::texture::const_part_shared_ptr &&
		);

		libftl::xml::generated::ship::gib gib_;

		sge::texture::const_part_shared_ptr image_;
	};

	object(
		base &&,
		fcppt::optional::object<
			shield
		> &&,
		fcppt::optional::object<
			floor
		> &&,
		fcppt::optional::object<
			cloak
		> &&,
		std::vector<
			gib_image
		> &&
	);

	base base_;

	fcppt::optional::object<
		shield
	> shield_;

	fcppt::optional::object<
		floor
	> floor_;

	fcppt::optional::object<
		cloak
	> cloak_;

	std::vector<
		gib_image
	> gibs_;
};

}
}
}

#endif
