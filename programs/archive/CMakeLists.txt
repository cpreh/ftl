find_package(
	Boost REQUIRED
	COMPONENTS filesystem
)

find_package(
	fcppt
	REQUIRED
)

add_executable(
	ftlarchive
	main.cpp
)

include(
	FcpptCMakeUtils
)

fcppt_utils_set_target_compiler_flags(
	ftlarchive
)

target_link_libraries(
	ftlarchive
	PRIVATE
	${libftl_TARGET}
	${fcppt_core_TARGET}
	${fcppt_filesystem_TARGET}
	${fcppt_options_TARGET}
	${fcppt_system_TARGET}
	${Boost_FILESYSTEM_LIBRARIES}
	${FCPPT_UTILS_MAIN_LINK_LIBS}
)

target_compile_definitions(
	ftlarchive
	PRIVATE
	${FCPPT_UTILS_MAIN_COMPILE_OPTIONS}
)
