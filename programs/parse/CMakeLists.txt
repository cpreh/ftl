find_package(fcppt REQUIRED)

fcppt_utils_load_source_files(programs/parse/files.txt FTLPARSE_FILES)

include(FcpptCMakeUtils)

fcppt_utils_append_source_dir_and_make_groups("${FTLPARSE_FILES}"
                                              FTLPARSE_FILES_ABS)

add_executable(ftlparse main.cpp ${FTLPARSE_FILES_ABS})

fcppt_utils_set_target_compiler_flags(ftlparse)

target_link_libraries(
  ftlparse PRIVATE ${libftl_TARGET} ${fcppt_core_TARGET}
                   ${fcppt_options_TARGET} ${FCPPT_UTILS_MAIN_LINK_LIBS})

target_include_directories(ftlparse PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(ftlparse PRIVATE ${FCPPT_UTILS_MAIN_COMPILE_OPTIONS})
