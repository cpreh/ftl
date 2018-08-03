#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/archive/filesystem.hpp>
#include <libftl/archive/path.hpp>
#include <libftl/sprite/color_format.hpp>
#include <libftl/sprite/draw.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/sprite/object.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/system_fwd.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/show_message.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/record/variadic.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <brigand/sequences/list.hpp>
#include <exception>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

FCPPT_RECORD_MAKE_LABEL(
	archive_label
);

FCPPT_RECORD_MAKE_LABEL(
	image_path_label
);

typedef
fcppt::record::variadic<
	fcppt::record::element<
		archive_label,
		boost::filesystem::path
	>,
	fcppt::record::element<
		image_path_label,
		libftl::archive::path
	>
>
argument_record;

awl::main::exit_code
main_loop(
	sge::renderer::device::ffp &_renderer_device,
	sge::window::system &_window_system,
	sge::texture::const_part_shared_ptr const _texture
)
{
	auto const draw(
		[
			&_renderer_device,
			&_texture
		]{
			sge::renderer::context::scoped_ffp const scoped_block(
				_renderer_device,
				_renderer_device.onscreen_target()
			);

			scoped_block.get().clear(
				sge::renderer::clear::parameters()
				.back_buffer(
					sge::image::color::any::object{
						sge::image::color::predef::black()
					}
				)
			);

			libftl::sprite::draw(
				_renderer_device,
				scoped_block.get(),
				std::vector<
					libftl::sprite::object
				>{
					libftl::sprite::object{
						sge::sprite::roles::pos{} =
							fcppt::math::vector::null<
								libftl::sprite::object::vector
							>(),
						sge::sprite::roles::texture0{} =
							libftl::sprite::object::texture_type{
								_texture
							},
						sge::sprite::roles::color{} =
							sge::image::color::convert<
								libftl::sprite::color_format
							>(
								sge::image::color::predef::white()
							)
					}
				}
			);
		}
	);

	return
		sge::window::loop(
			_window_system,
			sge::window::loop_function{
				[
					&draw
				](
					awl::event::base const &_event
				)
				{
					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							sge::renderer::event::render const
						>(
							_event
						),
						[
							&draw
						](
							fcppt::reference<
								sge::renderer::event::render const
							>
						)
						{
							draw();
						}
					);
				}
			}
		);
}

awl::main::exit_code
main_program(
	argument_record const &_arguments
)
{
	sge::systems::instance<
		brigand::list<
			sge::systems::with_window,
			sge::systems::with_renderer<
				sge::systems::renderer_caps::ffp
			>,
			sge::systems::with_input,
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::window{
				sge::systems::window_source{
					sge::systems::original_window{
						sge::window::title{
							FCPPT_TEXT("FTL draw")
						}
					}
				}
			}
		)
		(
			sge::systems::renderer{
				sge::renderer::pixel_format::object{
					sge::renderer::pixel_format::color::depth32,
					sge::renderer::pixel_format::depth_stencil::off,
					sge::renderer::pixel_format::optional_multi_samples(),
					sge::renderer::pixel_format::srgb::no
				},
				sge::renderer::display_mode::parameters{
					sge::renderer::display_mode::vsync::on,
					sge::renderer::display_mode::optional_object()
				},
				sge::viewport::optional_resize_callback{
					sge::viewport::fill_on_resize()
				}
			}
		)
		(
			sge::systems::input(
				sge::systems::cursor_option_field::null()
			)
		)
		(
			sge::systems::image2d(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					}
				)
			)
		)
	);

	libftl::archive::base_unique_ptr const archive{
		libftl::archive::filesystem(
			boost::filesystem::path{
				fcppt::record::get<
					archive_label
				>(
					_arguments
				)
			}
		)
	};

	libftl::sprite::images images{
		fcppt::make_ref(
			sys.renderer_device_core()
		),
		fcppt::make_ref(
			sys.image_system()
		),
		fcppt::make_ref(
			*archive
		)
	};

	return
		fcppt::either::match(
			images.load(
				fcppt::record::get<
					image_path_label
				>(
					_arguments
				)
			),
			[](
				libftl::error const &_error
			)
			{
				awl::show_error(
					fcppt::output_to_fcppt_string(
						_error
					)
				);

				return
					awl::main::exit_failure();
			},
			[
				&sys
			](
				sge::texture::const_part_shared_ptr const _texture
			)
			{
				return
					main_loop(
						sys.renderer_device_ffp(),
						sys.window_system(),
						_texture
					);
			}
		);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

awl::main::exit_code const
draw_main(
	awl::main::function_context const &_context
)
try
{
	auto const parser{
		fcppt::options::apply(
			fcppt::options::argument<
				archive_label,
				boost::filesystem::path
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("Archive")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Path to the FTL archive")
					}
				}
			},
			fcppt::options::argument<
				image_path_label,
				libftl::archive::path
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("Path")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("Path of the png file")
					}
				}
			}
		)
	};

	typedef
	decltype(
		parser
	)
	parser_type;

	return
		fcppt::variant::match(
			fcppt::options::parse_help(
				fcppt::options::default_help_switch(),
				parser,
				fcppt::args_from_second(
					_context.argc(),
					_context.argv()
				)
			),
			[](
				fcppt::options::result<
					fcppt::options::result_of<
						parser_type
					>
				> const &_result
			)
			{
				return
					fcppt::either::match(
						_result,
						[](
							fcppt::options::error const &_error
						)
						{
							awl::show_error(
								fcppt::output_to_fcppt_string(
									_error
								)
							);

							return
								awl::main::exit_failure();
						},
						[](
							fcppt::options::result_of<
								parser_type
							> const &_arguments
						)
						{
							return
								main_program(
									fcppt::record::permute<
										argument_record
									>(
										_arguments
									)
								);
						}
					);
			},
			[](
				fcppt::options::help_text const &_help_text
			)
			{
				awl::show_message(
					fcppt::output_to_fcppt_string(
						_help_text
					)
				);

				return
					awl::main::exit_success();
			}
		);
}
catch(
	fcppt::exception const &_error
)
{
	awl::show_error(
		_error.string()
	);

	return
		awl::main::exit_failure();
}
catch(
	std::exception const &_error
)
{
	awl::show_error_narrow(
		_error.what()
	);

	return
		awl::main::exit_failure();
}

FCPPT_PP_POP_WARNING
