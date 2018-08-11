#include <libftl/ship/images/object.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


libftl::ship::images::object::offset_image::offset_image(
	libftl::xml::generated::ship::offset const _offset,
	sge::texture::const_part_shared_ptr &&_image
)
:
	offset_{
		_offset
	},
	image_{
		std::move(
			_image
		)
	}
{
}

libftl::ship::images::object::gib_image::gib_image(
	libftl::xml::generated::ship::gib const _gib,
	sge::texture::const_part_shared_ptr &&_image
)
:
	gib_{
		_gib
	},
	image_{
		std::move(
			_image
		)
	}
{
}

libftl::ship::images::object::object(
	base &&_base,
	shield &&_shield,
	fcppt::optional::object<
		floor
	> &&_floor,
	fcppt::optional::object<
		cloak
	> &&_cloak,
	std::vector<
		gib_image
	> &&_gibs
)
:
	base_{
		std::move(
			_base
		)
	},
	shield_{
		std::move(
			_shield
		)
	},
	floor_{
		std::move(
			_floor
		)
	},
	cloak_{
		std::move(
			_cloak
		)
	},
	gibs_{
		std::move(
			_gibs
		)
	}
{
}
