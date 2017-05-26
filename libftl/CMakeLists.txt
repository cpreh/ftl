#find_package(
#	Boost REQUIRED
#	COMPONENTS filesystem
#)

find_package(
        fcppt
	REQUIRED
)

find_package(
	alda
	REQUIRED
)

find_package(
	XercesC
	REQUIRED
)

find_package(
	xsd
	REQUIRED
)

function(
	generate_xml_parser
	PARSER_NAME
)
	set(
		OUTPUT_DIR
		${CMAKE_CURRENT_BINARY_DIR}/xsd/include/libftl/xsd
	)

	set(
		PARSER_FILES
		${OUTPUT_DIR}/${PARSER_NAME}.hxx
		${OUTPUT_DIR}/${PARSER_NAME}-fwd.hxx
		${OUTPUT_DIR}/${PARSER_NAME}.cxx
	)

	set(
		XSD_FILE
		${FCPPT_UTILS_PROJECT_SOURCE_DIR}/xsd/${PARSER_NAME}.xsd
	)

	add_custom_command(
		OUTPUT
		${PARSER_FILES}
		COMMAND
			${XSD_PROGRAM}
			cxx-tree
			--std
			c++11
			--namespace-map
			=libftl::xml::generated
			--generate-forward
			${XSD_FILE}
		DEPENDS
		${XSD_FILE}
		WORKING_DIRECTORY
		${OUTPUT_DIR}
	)

	set(
		LIBFTL_PARSER_FILES
		${LIBFTL_PARSER_FILES}
		${PARSER_FILES}
		PARENT_SCOPE
	)
endfunction()

set(
	PARSER_NAMES
	sector
)

foreach(
	PARSER
	${PARSER_NAMES}
)
	generate_xml_parser(
		${PARSER}
	)
endforeach()

add_custom_target(
	xsdfiles
	DEPENDS
	${LIBFTL_PARSER_FILES}
)

set(
	LIBFTL_FILES
	libftl/include/libftl/archive/entry.hpp
	libftl/include/libftl/archive/entry_fwd.hpp
	libftl/include/libftl/archive/entry_output.hpp
	libftl/include/libftl/archive/extract.hpp
	libftl/include/libftl/archive/index.hpp
	libftl/include/libftl/archive/index_result.hpp
	libftl/include/libftl/archive/index_result_fwd.hpp
	libftl/include/libftl/archive/length.hpp
	libftl/include/libftl/archive/offset.hpp
	libftl/include/libftl/archive/read_index.hpp
	libftl/src/archive/entry_output.cpp
	libftl/src/archive/extract.cpp
	libftl/src/archive/read_index.cpp
)

set(
	LIBFTL_STATIC_LINK_FLAG
	LIBFTL_STATIC_LINK
)

include(
	FcpptSymbol
)

fcppt_generate_symbol_header(
	STATIC_LINK_FLAG
		"${LIBFTL_STATIC_LINK_FLAG}"
	EXPORTS_NAME
		"libftl"
	SYMBOL_NAME
		"LIBFTL_DETAIL"
)

function(
	add_libftl_library
	VARIANT
)
	if(
		${VARIANT} STREQUAL "STATIC"
	)
		fcppt_utils_static_link_name(
			libftl
			LIBFTL_LIB_NAME
		)
	else()
		set(
			LIBFTL_LIB_NAME
			libftl
		)
	endif()

	fcppt_utils_append_source_dir_and_make_groups(
		"${LIBFTL_FILES}"
		LIBFTL_FILES_ABS
	)

	add_library(
		${LIBFTL_LIB_NAME}
		${VARIANT}
		${LIBFTL_PARSER_FILES}
		${LIBFTL_FILES_ABS}
	)

	fcppt_utils_set_target_compiler_flags(
		${LIBFTL_LIB_NAME}
	)

#	${Boost_INCLUDE_DIRS}
	target_include_directories(
		${LIBFTL_LIB_NAME}
		PUBLIC
		${FCPPT_UTILS_PROJECT_BINARY_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/include
		PRIVATE
		${XercesC_INCLUDE_DIRS}
	)

	fcppt_utils_interface_static_link(
		${LIBFTL_LIB_NAME}
		${VARIANT}
		"${LIBFTL_STATIC_LINK_FLAG}"
	)

#${Boost_FILESYSTEM_LIBRARIES}
	target_link_libraries(
		${LIBFTL_LIB_NAME}
		PUBLIC
		fcppt_core_interface
		PRIVATE
		${XercesC_LIBRARIES}
		${alda_TARGET}
		${fcppt_core_TARGET}
	)

	add_dependencies(
		${LIBFTL_LIB_NAME}
		xsdfiles
	)

	fcppt_utils_export_install_target(
		${LIBFTL_LIB_NAME}
	)
endfunction()

if(
	ENABLE_SHARED
)
	add_libftl_library(
		"SHARED"
	)
endif()

if(
	ENABLE_STATIC
)
	add_libftl_library(
		"STATIC"
	)
endif()
