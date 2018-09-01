#include <libftl/error.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/impl/xsd/to_fcppt_optional.hpp>
#include <libftl/room/system.hpp>
#include <libftl/room/type.hpp>
#include <libftl/ship/initial_state.hpp>
#include <libftl/ship/state.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/xml/generated/blueprints.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/maybe_front.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xsd/cxx/tree/containers.hxx>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::either::object<
	libftl::error,
	fcppt::optional::object<
		libftl::room::system
	>
>
load_system(
	libftl::sprite::images &_images,
	::xsd::cxx::tree::sequence<
		libftl::xml::generated::blueprints::system
	> const &_room_list,
	libftl::room::type const _room_type
)
{
	return
		fcppt::optional::maybe(
			fcppt::container::maybe_front(
				_room_list
			),
			[]{
				return
					fcppt::either::make_success<libftl::error>(
						fcppt::optional::object<libftl::room::system>{}
					);
			},
			[&_images, _room_type]
			(fcppt::reference<libftl::xml::generated::blueprints::system const> const _system)
			{
				return
					fcppt::either::map(
						fcppt::optional::maybe(
							libftl::impl::xsd::to_fcppt_optional(
								fcppt::make_cref(_system.get().img())
							),
							[]{
								return
									fcppt::either::make_success<libftl::error>(
										fcppt::optional::object<sge::texture::const_part_shared_ptr>{}
									);
							},
							[&_images]
							(fcppt::reference<xml_schema::string const> const _name)
							{
								return
									fcppt::either::map(
										_images.load(
											libftl::archive::path{
												"ship"
											}
											/ "interior"
											/ (_name.get() + ".png")
										),
										[](sge::texture::const_part_shared_ptr const _texture)
										{
											return
												fcppt::optional::make(_texture);
										}
									);
							}
						),
						[&_system, _room_type]
						(fcppt::optional::object<sge::texture::const_part_shared_ptr> const _texture)
						{
							return
								fcppt::optional::make(
									libftl::room::system{
										_room_type,
										_texture,
										libftl::room::system::power{
											_system.get().power()
										},
										fcppt::optional::map(
											libftl::impl::xsd::to_fcppt_optional(
												fcppt::make_cref(_system.get().max())
											),
											[](fcppt::reference<::xml_schema::unsigned_int const> const _max)
											{
												return
													libftl::room::system::max_power{
														_max.get()
													};
											}
										),
										libftl::ship::layout::room_id{
											_system.get().room()
										},
										fcppt::optional::map(
											libftl::impl::xsd::to_fcppt_optional(
												fcppt::make_cref(_system.get().start())
											),
											[](fcppt::reference<::xml_schema::boolean const> const _start)
											{
												return
													libftl::room::system::available{
														_start.get()
													};
											}
										)
									}
								);
						}
					);
			}
		);
}

/*
std::vector<
	libftl::room::state
>
load_rooms(
	libftl::xml::generated::blueprints::system_list const &_systems
)
{
	return
		fcppt::optional::cat(
			std::vector<
				fcppt::optional::object<
					libftl::room::state
				>
			>{
				load_system(_systems.pilot(), libftl::room::type::pilot)
				// TODO...
			}
		);
}
*/

}

/*
fcppt::either::object<
	libftl::error,
	libftl::ship::state
>
libftl::ship::initial_state(
	libftl::xml::generated::ship::ship_root const &_ship_root,
	libftl::sprite::images &_images
)
{
	return
		libftl::ship::state{
			fcppt::optional::maybe(
				fcppt::optional::maybe_front(
					_ship_root.systemList()
				),
				[]{
					return
						std::vector<
							libftl::room::state
						>{};
				},
				[](
					fcppt::reference<
						libftl::xml::generated::blueprints::system_list const
					> const _systems
				)
				{
					return
						load_rooms(_systems.get());
				}
			)
		};
}
*/
