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
