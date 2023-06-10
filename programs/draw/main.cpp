#include <libftl/error.hpp>
#include <libftl/archive/base.hpp>
#include <libftl/archive/base_unique_ptr.hpp>
#include <libftl/blueprints/data.hpp>
#include <libftl/blueprints/load.hpp>
#include <libftl/options/create_resource_parser.hpp>
#include <libftl/options/open_archive.hpp>
#include <libftl/options/resource_label.hpp>
#include <libftl/options/resource_variant.hpp>
#include <libftl/ship/draw.hpp>
#include <libftl/ship/load.hpp>
#include <libftl/ship/resources.hpp>
#include <libftl/sprite/draw.hpp>
#include <libftl/sprite/images.hpp>
#include <libftl/sprite/resolution.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
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
#include <sge/viewport/aspect_from_screen_size.hpp>
#include <sge/viewport/maintain_aspect.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/object.hpp>
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
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/either/bind.hpp>
#include <fcppt/either/from_optional.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/options/usage.hpp>
#include <fcppt/options/usage_output.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/record/permute.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/variant/output.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace
{
FCPPT_RECORD_MAKE_LABEL(ship_name_label);

using argument_record = fcppt::record::object<
    fcppt::record::element<libftl::options::resource_label, libftl::options::resource_variant>,
    fcppt::record::element<ship_name_label, fcppt::string>>;

struct resources
{
  resources(
      libftl::archive::base_unique_ptr &&_archive,
      libftl::sprite::images &&_images,
      libftl::blueprints::data &&_blueprints,
      libftl::ship::resources &&_ship)
      : archive_{std::move(_archive)},
        images_{std::move(_images)},
        blueprints_{std::move(_blueprints)},
        ship_{std::move(_ship)}
  {
  }

  libftl::archive::base_unique_ptr archive_;

  libftl::sprite::images images_;

  libftl::blueprints::data blueprints_;

  libftl::ship::resources ship_;
};

awl::main::exit_code main_loop(
    sge::renderer::device::ffp &_renderer_device, // NOLINT(google-runtime-references)
    sge::window::system &_window_system, // NOLINT(google-runtime-references)
    resources &&_resources)
{
  auto const draw(
      [&_renderer_device, &_resources]
      {
        sge::renderer::context::scoped_ffp const scoped_block(
            fcppt::make_ref(_renderer_device),
            fcppt::reference_to_base<sge::renderer::target::base>(
                fcppt::make_ref(_renderer_device.onscreen_target())));

        scoped_block.get().clear(sge::renderer::clear::parameters().back_buffer(
            sge::image::color::any::object{sge::image::color::predef::blue()}));

        libftl::sprite::draw(
            _renderer_device,
            scoped_block.get(),
            libftl::ship::draw(_resources.images_, _resources.ship_));
      });

  return sge::window::loop(
      _window_system,
      sge::window::loop_function{
          [&draw](awl::event::base const &_event)
          {
            fcppt::optional::maybe_void(
                fcppt::cast::dynamic<sge::renderer::event::render const>(_event),
                [&draw](fcppt::reference<sge::renderer::event::render const>) { draw(); });
          }});
}

awl::main::exit_code main_program(argument_record const &_arguments)
{
  sge::systems::instance<
      sge::systems::with_window,
      sge::systems::with_renderer<sge::systems::renderer_caps::ffp>,
      sge::systems::with_input,
      sge::systems::with_image2d> const sys(sge::systems::make_list(sge::systems::window{
      sge::systems::window_source{sge::systems::original_window{
          sge::window::title{FCPPT_TEXT("FTL draw")}}}}.dont_show())(sge::systems::renderer{
      sge::renderer::pixel_format::object{
          sge::renderer::pixel_format::color::depth32,
          sge::renderer::pixel_format::depth_stencil::off,
          sge::renderer::pixel_format::optional_multi_samples(),
          sge::renderer::pixel_format::srgb::no},
      sge::renderer::display_mode::parameters{
          sge::renderer::display_mode::vsync::on, sge::renderer::display_mode::optional_object()},
      sge::viewport::optional_resize_callback{sge::viewport::maintain_aspect(
          sge::viewport::aspect_from_screen_size(libftl::sprite::resolution()))}})(
      sge::systems::input(sge::systems::cursor_option_field::null()))(
      sge::systems::image2d(sge::media::optional_extension_set(
          sge::media::extension_set{sge::media::extension(FCPPT_TEXT("png"))}))));

  return fcppt::either::match(
      fcppt::either::bind(
          libftl::options::open_archive(
              fcppt::record::get<libftl::options::resource_label>(_arguments)),
          [&sys, &_arguments](libftl::archive::base_unique_ptr &&_archive)
          {
            libftl::sprite::images images{
                fcppt::make_ref(sys.renderer_device_core()),
                fcppt::make_ref(sys.image_system()),
                fcppt::make_ref(*_archive)};

            return fcppt::either::bind(
                libftl::blueprints::load(*_archive),
                [&_archive, &_arguments, &images](libftl::blueprints::data &&_blueprints)
                {
                  fcppt::string const &ship_name{fcppt::record::get<ship_name_label>(_arguments)};

                  return fcppt::either::bind(
                      fcppt::either::from_optional(
                          fcppt::to_std_string(ship_name),
                          [&ship_name] {
                            return libftl::error{
                                FCPPT_TEXT("Failed to convert ship name") + ship_name};
                          }),
                      [&_archive, &images, &_blueprints](std::string const &_name)
                      {
                        return fcppt::either::map(
                            libftl::ship::load(
                                *_archive, fcppt::make_cref(_blueprints), images, _name),
                            [&_blueprints, &images, &_archive](libftl::ship::resources &&_ship)
                            {
                              return resources{
                                  std::move(_archive),
                                  std::move(images),
                                  std::move(_blueprints),
                                  std::move(_ship)};
                            });
                      });
                });
          }),
      [](libftl::error const &_error)
      {
        awl::show_error(fcppt::output_to_fcppt_string(_error));

        return awl::main::exit_failure();
      },
      [&sys](resources &&_resources)
      {
        sys.window().show();

        return main_loop(sys.renderer_device_ffp(), sys.window_system(), std::move(_resources));
      });
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wmissing-prototypes)
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

awl::main::exit_code draw_main(awl::main::function_context const &_context)
try
{
  auto const parser{fcppt::options::apply(
      libftl::options::create_resource_parser(),
      fcppt::options::argument<ship_name_label, fcppt::string>{
          fcppt::options::long_name{FCPPT_TEXT("ShipName")},
          fcppt::options::optional_help_text{
              fcppt::options::help_text{FCPPT_TEXT("Name of the ship blueprint")}}})};

  using parser_type = decltype(parser);

  return fcppt::variant::match(
      fcppt::options::parse_help(
          fcppt::options::default_help_switch(),
          parser,
          fcppt::args_from_second(_context.argc(), _context.argv())),
      [](fcppt::options::result<fcppt::options::result_of<parser_type>> const &_result)
      {
        return fcppt::either::match(
            _result,
            [](fcppt::options::error const &_error)
            {
              awl::show_error(fcppt::output_to_fcppt_string(_error));

              return awl::main::exit_failure();
            },
            [](fcppt::options::result_of<parser_type> const &_arguments)
            { return main_program(fcppt::record::permute<argument_record>(_arguments)); });
      },
      [](fcppt::options::usage const &_usage)
      {
        awl::show_message(fcppt::output_to_fcppt_string(_usage));

        return awl::main::exit_success();
      });
}
catch (fcppt::exception const &_error)
{
  awl::show_error(_error.string());

  return awl::main::exit_failure();
}
catch (std::exception const &_error)
{
  awl::show_error_narrow(_error.what());

  return awl::main::exit_failure();
}

FCPPT_PP_POP_WARNING
