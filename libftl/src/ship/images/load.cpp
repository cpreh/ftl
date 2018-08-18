#include <libftl/error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/impl/xsd/to_fcppt_optional.hpp>
#include <libftl/ship/images/load.hpp>
#include <libftl/ship/images/name.hpp>
#include <libftl/ship/images/object.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <libftl/xml/generated/ship.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/either/apply.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/map_failure.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/tree/containers.hxx>
#include <string>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::either::object<
	libftl::error,
	sge::texture::const_part_shared_ptr
>
find_image(
	libftl::sprite::images &_images,
	std::string const &_file_name
)
{
	return
		fcppt::either::match(
			_images.load(libftl::archive::path{"ship"} / std::string{_file_name}),
			[&_file_name, &_images](libftl::error &&_error1)
			{
				return
					fcppt::either::map_failure(
						_images.load(libftl::archive::path{"ships_noglow"} / std::string{_file_name}),
						[&_error1](libftl::error &&_error2)
						{
							return
								libftl::error{
									std::move(_error1.get())
									+ FCPPT_TEXT("\n")
									+ std::move(_error2.get())
								};
						}
					);
			},
			[](sge::texture::const_part_shared_ptr &&_texture)
			{
				return
					fcppt::either::make_success<libftl::error>(std::move(_texture));
			}
		);
}

fcppt::either::object<
	libftl::error,
	libftl::ship::images::object::base
>
load_base(
	libftl::sprite::images &_images,
	libftl::ship::images::name const &_ship_name
)
{
	return
		fcppt::either::map(
			find_image(_images, _ship_name.get() + "_base.png"),
			[](sge::texture::const_part_shared_ptr &&_texture)
			{
				return
					libftl::ship::images::object::base{std::move(_texture)};
			}
		);
}

fcppt::either::object<
	libftl::error,
	fcppt::optional::object<
		libftl::ship::images::object::shield
	>
>
load_shield(
	libftl::sprite::images &_images,
	libftl::xml::generated::blueprints::ship_blueprint const &_blueprint
)
{
	return
		fcppt::optional::maybe(
			fcppt::container::maybe_front(_blueprint.shieldImage()),
			[]{
				return
					fcppt::either::make_success<libftl::error>(
						fcppt::optional::object<
							libftl::ship::images::object::shield
						>{}
					);
			},
			[&_images]
			(fcppt::reference<xml_schema::string const> const _shield)
			{
				return
					fcppt::either::map(
						find_image(
							_images,
							std::string{
								_shield.get()
								+ "_shields1.png"
							}
						),
						[](sge::texture::const_part_shared_ptr &&_texture)
						{
							return
								fcppt::optional::make(
									libftl::ship::images::object::shield{
										std::move(_texture)
									}
								);
						}
					);
			}
		);
}

typedef
fcppt::function<
	xsd::cxx::tree::optional<libftl::xml::generated::ship::offset> const & (
		libftl::xml::generated::ship::offsets const &
	)
>
get_offset_function;

template<
	typename Type
>
fcppt::either::object<
	libftl::error,
	fcppt::optional::object<
		Type
	>
>
load_offset_image(
	libftl::sprite::images &_images,
	fcppt::reference<
		libftl::xml::generated::ship::ship_root const
	> const _ship,
	get_offset_function const &_get_offset,
	std::string const &_name
)
{
	auto const image_from_offset(
		[&_images,&_name]
		(fcppt::reference<libftl::xml::generated::ship::offset const > const _offset)
		{
			return
				fcppt::either::map(
					find_image(_images, _name),
					[&_offset](sge::texture::const_part_shared_ptr &&_texture)
					{
						return
							fcppt::optional::make(
								Type{
									libftl::ship::images::object::offset_image{
										_offset.get(),
										std::move(_texture)
									}
								}
							);
					}
				);
		}
	);

	return
		fcppt::optional::maybe(
			fcppt::optional::bind(
				libftl::impl::xsd::to_fcppt_optional(fcppt::make_cref(_ship.get().offsets())),
				[&_get_offset]
				(fcppt::reference<libftl::xml::generated::ship::offsets const > const _offsets)
				{
					return
						libftl::impl::xsd::to_fcppt_optional(
							fcppt::make_cref(_get_offset(_offsets.get()))
						);
				}
			),
			[]{
				return
					fcppt::either::make_success<libftl::error>(
						fcppt::optional::object<Type>{}
					);
			},
			image_from_offset
		);
}

fcppt::either::object<
	libftl::error,
	libftl::ship::images::object::gib_image
>
load_mandatory_gib(
	libftl::sprite::images &_images,
	fcppt::reference<
		libftl::xml::generated::ship::gib const
	> const _gib,
	libftl::ship::images::name const &_ship_name,
	unsigned const _number
)
{
	return
		fcppt::either::map(
			find_image(_images, _ship_name.get() + "_gib" + fcppt::output_to_std_string(_number) + ".png"),
			[_gib](sge::texture::const_part_shared_ptr &&_texture)
			{
				return
					libftl::ship::images::object::gib_image(_gib.get(), std::move(_texture));
			}
		);
}

fcppt::either::object<
	libftl::error,
	fcppt::optional::object<
		libftl::ship::images::object::gib_image
	>
>
load_optional_gib(
	libftl::sprite::images &_images,
	fcppt::reference<
		::xsd::cxx::tree::optional<
			libftl::xml::generated::ship::gib
		> const
	> const _opt_gib,
	libftl::ship::images::name const &_ship_name,
	unsigned const _number
)
{
	return
		fcppt::optional::maybe(
			libftl::impl::xsd::to_fcppt_optional(fcppt::make_cref(_opt_gib.get())),
			[]{
				return
					fcppt::either::make_success<libftl::error>(
						fcppt::optional::object<libftl::ship::images::object::gib_image>{}
					);
			},
			[&_images,&_ship_name,&_number]
			(fcppt::reference<libftl::xml::generated::ship::gib const> const _gib)
			{
				return
					fcppt::either::map(
						load_mandatory_gib(_images,_gib,_ship_name,_number),
						[](libftl::ship::images::object::gib_image &&_gib_image)
						{
							return
								fcppt::optional::make(_gib_image);
						}
					);
			}
		);
}

fcppt::either::object<
	libftl::error,
	std::vector<
		libftl::ship::images::object::gib_image
	>
>
load_gibs(
	libftl::sprite::images &_images,
	fcppt::reference<
		libftl::xml::generated::ship::explosion const
	> const _explosion,
	libftl::ship::images::name const &_ship_name
)
{
	auto const load_mandatory_impl(
		[&_ship_name,&_images]
		(fcppt::reference<libftl::xml::generated::ship::gib const> const _gib, unsigned const _number)
		{
			return
				load_mandatory_gib(_images,_gib,_ship_name,_number);
		}
	);

	auto const load_optional_impl(
		[&_ship_name,&_images](
			fcppt::reference<::xsd::cxx::tree::optional<libftl::xml::generated::ship::gib> const> const _gib,
			unsigned const _number
		)
		{
			return
				load_optional_gib(_images,_gib,_ship_name,_number);
		}
	);

	return
		fcppt::either::apply(
			[](
				libftl::ship::images::object::gib_image &&_gib1,
				libftl::ship::images::object::gib_image &&_gib2,
				libftl::ship::images::object::gib_image &&_gib3,
				libftl::ship::images::object::gib_image &&_gib4,
				fcppt::optional::object<
					libftl::ship::images::object::gib_image
				> &&_gib5,
				fcppt::optional::object<
					libftl::ship::images::object::gib_image
				> &&_gib6
			)
			{
				return
					fcppt::algorithm::join(
						std::vector<libftl::ship::images::object::gib_image>
						{
							std::move(_gib1),
							std::move(_gib2),
							std::move(_gib3),
							std::move(_gib4)
						},
						fcppt::optional::to_container<
							std::vector<libftl::ship::images::object::gib_image>
						>(
							std::move(_gib5)
						),
						fcppt::optional::to_container<
							std::vector<libftl::ship::images::object::gib_image>
						>(
							std::move(_gib6)
						)
					);
			},
			load_mandatory_impl(fcppt::make_cref(_explosion.get().gib1()), 1u),
			load_mandatory_impl(fcppt::make_cref(_explosion.get().gib2()), 2u),
			load_mandatory_impl(fcppt::make_cref(_explosion.get().gib3()), 3u),
			load_mandatory_impl(fcppt::make_cref(_explosion.get().gib4()), 4u),
			load_optional_impl(fcppt::make_cref(_explosion.get().gib5()), 5u),
			load_optional_impl(fcppt::make_cref(_explosion.get().gib6()), 6u)
		);
}

}

fcppt::either::object<
	libftl::error,
	libftl::ship::images::object
>
libftl::ship::images::load(
	libftl::sprite::images &_images,
	libftl::xml::generated::blueprints::ship_blueprint const &_blueprint,
	fcppt::reference<
		libftl::xml::generated::ship::ship_root const
	> const _ship,
	libftl::ship::images::name const &_ship_name
)
{
	return
		fcppt::either::apply(
			[](
				libftl::ship::images::object::base &&_base,
				fcppt::optional::object<libftl::ship::images::object::shield> &&_shield,
				fcppt::optional::object<libftl::ship::images::object::floor> &&_floor,
				fcppt::optional::object<libftl::ship::images::object::cloak> &&_cloak,
				std::vector<libftl::ship::images::object::gib_image> &&_gibs
			)
			{
				return
					libftl::ship::images::object{
						std::move(_base),
						std::move(_shield),
						std::move(_floor),
						std::move(_cloak),
						std::move(_gibs)
					};
			},
			load_base(_images, _ship_name),
			load_shield(_images, _blueprint),
			load_offset_image<libftl::ship::images::object::floor>(
				_images, _ship,
				get_offset_function{
					[](libftl::xml::generated::ship::offsets const &_offset)
					->
					xsd::cxx::tree::optional<libftl::xml::generated::ship::offset> const &
					{
						return
							_offset.floor();
					}
				},
				_ship_name.get() + "_floor.png"
			),
			load_offset_image<libftl::ship::images::object::cloak>(
				_images, _ship,
				get_offset_function{
					[](libftl::xml::generated::ship::offsets const &_offset)
					->
					xsd::cxx::tree::optional<libftl::xml::generated::ship::offset> const &
					{
						return
							_offset.cloak();
					}
				},
				fcppt::optional::from(
					fcppt::optional::map(
						fcppt::container::maybe_front(_blueprint.cloakImage()),
						[](fcppt::reference<xml_schema::string const> const _cloak)
						{
							return
								std::string{_cloak.get()};
						}
					),
					[&_ship_name]{
						// TODO: Do we need this?
						return
							_ship_name.get();
					}
				)
				+ "_cloak.png"
			),
			load_gibs(_images, fcppt::make_cref(_ship.get().explosion()), _ship_name)
		);
}
