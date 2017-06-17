add_executable(
	ftlship
	main.cpp
)

include(
	FcpptCMakeUtils
)

fcppt_utils_set_target_compiler_flags(
	ftlship
)


target_link_libraries(
	ftlship
	PRIVATE
	${libftl_TARGET}
	${fcppt_core_TARGET}
	${fcppt_filesystem_TARGET}
	${fcppt_options_TARGET}
	${FCPPT_UTILS_MAIN_LINK_LIBS}
	${Boost_FILESYSTEM_LIBRARIES}
)

target_compile_definitions(
	ftlship
	PRIVATE
	${FCPPT_UTILS_MAIN_COMPILE_OPTIONS}
)
