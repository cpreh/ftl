find_package(fcppt REQUIRED)

find_package(mizuiro REQUIRED)

find_package(awl REQUIRED)

find_package(
  sge REQUIRED
  COMPONENTS imagecolor
             media
             renderer
             sprite
             systems
             texture
             viewport
             window)

include(AwlMainGenerator)

awl_utils_add_portable_executable(ftldraw "draw_main" main.cpp)

include(FcpptCMakeUtils)

fcppt_utils_set_target_compiler_flags(ftldraw)

target_link_libraries(
  ftldraw
  PRIVATE ${libftl_TARGET}
          ${sgeimagecolor_TARGET}
          ${sgemedia_TARGET}
          ${sgerenderer_TARGET}
          ${sgesprite_TARGET}
          ${sgesystems_TARGET}
          ${sgetexture_TARGET}
          ${sgeviewport_TARGET}
          ${sgewindow_TARGET}
          ${awl_TARGET}
          ${fcppt_core_TARGET}
          ${fcppt_filesystem_TARGET}
          ${fcppt_options_TARGET})

target_compile_options(ftldraw PRIVATE ${FCPPT_UTILS_MAIN_COMPILE_OPTIONS})
