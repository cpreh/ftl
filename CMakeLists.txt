cmake_minimum_required(
	VERSION
	3.3
)

project(
	ftl
)

list(
	APPEND
	CMAKE_MODULE_PATH
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
)

find_package(
	fcppt
	REQUIRED
)

set(
	FCPPT_UTILS_CLANG_TIDY_ADDITIONAL_CHECKS
	"-fuchsia-default-arguments-calls"
	"-fuchsia-default-arguments-declarations"
	"-misc-non-private-member-variables-in-classes"
)

include(
	FcpptCMakeUtils
)

fcppt_utils_static_shared()

fcppt_utils_link_target(
	libftl
)

add_subdirectory(
	libftl
)

add_subdirectory(
	programs
)

option(
	ENABLE_TEST
	"Build the tests"
	ON
)

if(
	ENABLE_TEST
)
	find_package(
		Catch2
		REQUIRED
	)

	fcppt_utils_setup_tests()

	enable_testing()

	add_subdirectory(
		test
	)
endif()
