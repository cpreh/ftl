function(
	add_ftl_test
)
	fcppt_utils_add_test(
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/test
		${ARGN}
	)
endfunction()

add_ftl_test(
	xml/typed/attribute
	LINK_LIBS
		libftl_impl_interface
		fcppt_catch_interface
		fcppt_core_interface
)

add_ftl_test(
	xml/typed/content
	LINK_LIBS
		libftl_impl_interface
		fcppt_catch_interface
		fcppt_core_interface
)

add_ftl_test(
	xml/typed/empty
	LINK_LIBS
		libftl_impl_interface
		fcppt_catch_interface
		fcppt_core_interface
)
