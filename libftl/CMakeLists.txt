find_package(awl REQUIRED)

find_package(mizuiro REQUIRED)

find_package(fcppt REQUIRED)

find_package(alda REQUIRED)

find_package(sge REQUIRED COMPONENTS image2d imagecolor media renderer sprite
                                     texture)

fcppt_utils_load_source_files(libftl/files.txt LIBFTL_FILES)

set(LIBFTL_STATIC_LINK_FLAG LIBFTL_STATIC_LINK)

include(FcpptSymbol)

fcppt_generate_symbol_header(STATIC_LINK_FLAG "${LIBFTL_STATIC_LINK_FLAG}"
                             EXPORTS_NAME "libftl" SYMBOL_NAME "LIBFTL_DETAIL")

function(add_libftl_library VARIANT)
  if(${VARIANT} STREQUAL "STATIC")
    fcppt_utils_static_link_name(libftl LIBFTL_LIB_NAME)
  elseif(${VARIANT} STREQUAL "INTERFACE")
    fcppt_utils_interface_link_name(libftl LIBFTL_LIB_NAME)
  else()
    set(LIBFTL_LIB_NAME libftl)
  endif()

  fcppt_utils_append_source_dir_and_make_groups("${LIBFTL_FILES}"
                                                LIBFTL_FILES_ABS)

  if(${VARIANT} STREQUAL "INTERFACE")
    add_library(${LIBFTL_LIB_NAME} ${VARIANT})
  else()
    add_library(${LIBFTL_LIB_NAME} ${VARIANT} ${LIBFTL_PARSER_FILES}
                                   ${LIBFTL_FILES_ABS})
  endif()

  if(NOT ${VARIANT} STREQUAL "INTERFACE")
    fcppt_utils_set_target_compiler_flags(${LIBFTL_LIB_NAME})
  endif()

  target_include_directories(${LIBFTL_LIB_NAME}
                             INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

  if(NOT ${VARIANT} STREQUAL "INTERFACE")
    target_include_directories(
      ${LIBFTL_LIB_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
                                 ${CMAKE_CURRENT_SOURCE_DIR}/impl/include)
  endif()

  target_include_directories(
    ${LIBFTL_LIB_NAME} SYSTEM
    INTERFACE ${FCPPT_UTILS_PROJECT_BINARY_DIR}/include)

  if(NOT ${VARIANT} STREQUAL "INTERFACE")
    target_include_directories(
      ${LIBFTL_LIB_NAME} SYSTEM
      PRIVATE ${FCPPT_UTILS_PROJECT_BINARY_DIR}/include)
  endif()

  fcppt_utils_interface_static_link(${LIBFTL_LIB_NAME} ${VARIANT}
                                    "${LIBFTL_STATIC_LINK_FLAG}")

  target_link_libraries(
    ${LIBFTL_LIB_NAME}
    INTERFACE sgeimagecolor_interface sgerenderer_interface sgesprite_interface
              fcppt_core_interface fcppt_options_interface
              fcppt_parse_interface)

  if(NOT ${VARIANT} STREQUAL "INTERFACE")
    target_link_libraries(
      ${LIBFTL_LIB_NAME}
      PRIVATE ${sgeimagecolor_TARGET}
              ${sgeimage2d_TARGET}
              ${sgemedia_TARGET}
              ${sgeparse_TARGET}
              ${sgerenderer_TARGET}
              ${sgesprite_TARGET}
              ${sgetexture_TARGET}
              ${alda_TARGET}
              ${fcppt_core_TARGET}
              ${fcppt_options_TARGET}
              fcppt_parse_interface)
  endif()

  fcppt_utils_export_install_target(${LIBFTL_LIB_NAME})
endfunction()

if(ENABLE_SHARED)
  add_libftl_library("SHARED")
endif()

if(ENABLE_STATIC)
  add_libftl_library("STATIC")
endif()

add_libftl_library("INTERFACE")

add_library(libftl_impl_interface INTERFACE)

target_include_directories(libftl_impl_interface
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/impl/include)

target_link_libraries(libftl_impl_interface INTERFACE libftl_interface)
