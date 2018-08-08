find_package(
	Boost REQUIRED
	COMPONENTS filesystem
)

find_package(
	fcppt
	REQUIRED
)

set(
	FTLPARSE_FILES
	programs/parse/include/ftl/parse/path_label.hpp
	programs/parse/include/ftl/parse/ship/arguments.hpp
	programs/parse/include/ftl/parse/ship/arguments_fwd.hpp
	programs/parse/include/ftl/parse/ship/main.hpp
	programs/parse/include/ftl/parse/ship/options_parser.hpp
	programs/parse/src/ftl/parse/ship/main.cpp
	programs/parse/src/ftl/parse/ship/options_parser.cpp
)

include(
	FcpptCMakeUtils
)

fcppt_utils_append_source_dir_and_make_groups(
	"${FTLPARSE_FILES}"
	FTLPARSE_FILES_ABS
)

add_executable(
	ftlparse
	main.cpp
	${FTLPARSE_FILES_ABS}
)

fcppt_utils_set_target_compiler_flags(
	ftlparse
)

target_link_libraries(
	ftlparse
	PRIVATE
	${libftl_TARGET}
	${fcppt_core_TARGET}
	${fcppt_options_TARGET}
	${FCPPT_UTILS_MAIN_LINK_LIBS}
	${Boost_FILESYSTEM_LIBRARIES}
)

target_include_directories(
	ftlparse
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${Boost_INCLUDE_DIRS}
)

target_compile_definitions(
	ftlparse
	PRIVATE
	${FCPPT_UTILS_MAIN_COMPILE_OPTIONS}
)
