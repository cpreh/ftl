cmake_minimum_required(
	VERSION
	3.3
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
