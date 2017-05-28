#find_package(
#	Boost REQUIRED
#	COMPONENTS filesystem
#)

find_package(
	fcppt
	REQUIRED
)

add_executable(
	ftlxml
	main.cpp
)

include(
	FcpptCMakeUtils
)

fcppt_utils_set_target_compiler_flags(
	ftlxml
)


target_link_libraries(
	ftlxml
	PRIVATE
	${libftl_TARGET}
	${fcppt_core_TARGET}
	${fcppt_filesystem_TARGET}
	${fcppt_options_TARGET}
	${FCPPT_UTILS_MAIN_LINK_LIBS}
	${Boost_FILESYSTEM_LIBRARIES}
)

target_compile_definitions(
	ftlxml
	PRIVATE
	${FCPPT_UTILS_MAIN_COMPILE_OPTIONS}
)
