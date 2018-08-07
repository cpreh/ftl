find_package(
	Boost REQUIRED
	COMPONENTS filesystem
)

find_package(
	Brigand
	REQUIRED
)

find_package(
	awl
	REQUIRED
)

find_package(
	mizuiro
	REQUIRED
)

find_package(
        fcppt
	REQUIRED
)

find_package(
	alda
	REQUIRED
)

find_package(
	sge
	REQUIRED
	COMPONENTS
	image2d
	imagecolor
	media
	parse
	renderer
	sprite
	texture
)

find_package(
	XercesC
	REQUIRED
)

find_package(
	xsd
	REQUIRED
)

set(
	GENERATED_XSD_INCLUDE_DIR
	${FCPPT_UTILS_PROJECT_BINARY_DIR}/xsd/include
)

function(
	generate_xml_parser
	PARSER_NAME
)
	set(
		OUTPUT_DIR
		${GENERATED_XSD_INCLUDE_DIR}/libftl/xml/generated
	)

	set(
		PARSER_FILES
		${OUTPUT_DIR}/${PARSER_NAME}.hpp
		${OUTPUT_DIR}/${PARSER_NAME}_fwd.hpp
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
			=libftl::xml::generated::${PARSER_NAME}
			--hxx-prologue
			"#include <libftl/detail/symbol.hpp>"
			--hxx-prologue
			"#include <fcppt/config/external_begin.hpp>"
			--hxx-epilogue
			"#include <fcppt/config/external_end.hpp>"
			--hxx-suffix
			".hpp"
			--fwd-suffix
			"_fwd.hpp"
			--generate-forward
			--generate-ostream
			--guard-prefix
			LIBFTL_XML_GENERATED
			--export-symbol
			LIBFTL_DETAIL_SYMBOL
			--output-dir
			${OUTPUT_DIR}
			${XSD_FILE}
		DEPENDS
		${XSD_FILE}
		VERBATIM
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
	achievements
	animations
	blueprints
	events
	sectors
	ship
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
	libftl/impl/include/libftl/impl/archive/chain.hpp
	libftl/impl/include/libftl/impl/archive/filesystem.hpp
	libftl/impl/include/libftl/impl/archive/native.hpp
	libftl/impl/include/libftl/impl/spirit/variant_decl.hpp
	libftl/impl/include/libftl/impl/spirit/variant_fwd.hpp
	libftl/impl/include/libftl/impl/spirit/variant_impl.hpp
	libftl/impl/include/libftl/impl/spirit/variant_output.hpp
	libftl/impl/include/libftl/impl/xml/document.hpp
	libftl/impl/include/libftl/impl/xml/document_fwd.hpp
	libftl/impl/include/libftl/impl/xml/document_output.hpp
	libftl/impl/include/libftl/impl/xml/file_to_string.hpp
	libftl/impl/include/libftl/impl/xml/load_function.hpp
	libftl/impl/include/libftl/impl/xml/make_load_function.hpp
	libftl/impl/include/libftl/impl/xml/output.hpp
	libftl/impl/include/libftl/impl/xml/parse.hpp
	libftl/impl/include/libftl/impl/xml/read.hpp
	libftl/impl/include/libftl/impl/xml/remove_comments.hpp
	libftl/impl/src/impl/archive/chain.cpp
	libftl/impl/src/impl/archive/filesystem.cpp
	libftl/impl/src/impl/archive/native.cpp
	libftl/impl/src/impl/xml/document_output.cpp
	libftl/impl/src/impl/xml/file_to_string.cpp
	libftl/impl/src/impl/xml/output.cpp
	libftl/impl/src/impl/xml/parse.cpp
	libftl/impl/src/impl/xml/remove_comments.cpp
	libftl/include/libftl/archive/base.hpp
	libftl/include/libftl/archive/base_fwd.hpp
	libftl/include/libftl/archive/base_unique_ptr.hpp
	libftl/include/libftl/archive/chain.hpp
	libftl/include/libftl/archive/entry.hpp
	libftl/include/libftl/archive/entry_fwd.hpp
	libftl/include/libftl/archive/entry_output.hpp
	libftl/include/libftl/archive/extract.hpp
	libftl/include/libftl/archive/file.hpp
	libftl/include/libftl/archive/file_fwd.hpp
	libftl/include/libftl/archive/filesystem.hpp
	libftl/include/libftl/archive/index.hpp
	libftl/include/libftl/archive/length.hpp
	libftl/include/libftl/archive/offset.hpp
	libftl/include/libftl/archive/open.hpp
	libftl/include/libftl/archive/path.hpp
	libftl/include/libftl/archive/path_fwd.hpp
	libftl/include/libftl/archive/read_index.hpp
	libftl/include/libftl/error.hpp
	libftl/include/libftl/error_fwd.hpp
	libftl/include/libftl/options/create_resource_parser.hpp
	libftl/include/libftl/options/data_file_label.hpp
	libftl/include/libftl/options/native_resource_record.hpp
	libftl/include/libftl/options/native_resource_record_fwd.hpp
	libftl/include/libftl/options/open_archive.hpp
	libftl/include/libftl/options/resource_file_label.hpp
	libftl/include/libftl/options/resource_label.hpp
	libftl/include/libftl/options/resource_parser.hpp
	libftl/include/libftl/options/resource_parser_fwd.hpp
	libftl/include/libftl/options/resource_path_label.hpp
	libftl/include/libftl/options/resource_record.hpp
	libftl/include/libftl/options/resource_record_fwd.hpp
	libftl/include/libftl/options/resource_variant.hpp
	libftl/include/libftl/options/resource_variant_fwd.hpp
	libftl/include/libftl/options/unpacked_resource_record.hpp
	libftl/include/libftl/options/unpacked_resource_record_fwd.hpp
	libftl/include/libftl/ship/door.hpp
	libftl/include/libftl/ship/door_fwd.hpp
	libftl/include/libftl/ship/ellipse.hpp
	libftl/include/libftl/ship/ellipse_fwd.hpp
	libftl/include/libftl/ship/layout.hpp
	libftl/include/libftl/ship/layout_fwd.hpp
	libftl/include/libftl/ship/layout_output.hpp
	libftl/include/libftl/ship/parse_layout.hpp
	libftl/include/libftl/ship/room.hpp
	libftl/include/libftl/ship/room_fwd.hpp
	libftl/include/libftl/ship/room_id.hpp
	libftl/include/libftl/ship/tile_coordinate.hpp
	libftl/include/libftl/ship/tile_pos.hpp
	libftl/include/libftl/ship/tile_pos_fwd.hpp
	libftl/include/libftl/ship/tile_rect.hpp
	libftl/include/libftl/ship/tile_rect_fwd.hpp
	libftl/include/libftl/sprite/choices.hpp
	libftl/include/libftl/sprite/color_format.hpp
	libftl/include/libftl/sprite/draw.hpp
	libftl/include/libftl/sprite/images.hpp
	libftl/include/libftl/sprite/images_fwd.hpp
	libftl/include/libftl/sprite/object.hpp
	libftl/include/libftl/xml/achievements.hpp
	libftl/include/libftl/xml/animations.hpp
	libftl/include/libftl/xml/blueprints.hpp
	libftl/include/libftl/xml/clean.hpp
	libftl/include/libftl/xml/events.hpp
	libftl/include/libftl/xml/result.hpp
	libftl/include/libftl/xml/result_fwd.hpp
	libftl/include/libftl/xml/sectors.hpp
	libftl/include/libftl/xml/ship.hpp
	libftl/src/archive/base.cpp
	libftl/src/archive/chain.cpp
	libftl/src/archive/entry_output.cpp
	libftl/src/archive/extract.cpp
	libftl/src/archive/filesystem.cpp
	libftl/src/archive/open.cpp
	libftl/src/archive/path.cpp
	libftl/src/archive/read_index.cpp
	libftl/src/options/create_resource_parser.cpp
	libftl/src/options/open_archive.cpp
	libftl/src/ship/layout.cpp
	libftl/src/ship/layout_output.cpp
	libftl/src/ship/parse_layout.cpp
	libftl/src/sprite/draw.cpp
	libftl/src/sprite/images.cpp
	libftl/src/xml/achievements.cpp
	libftl/src/xml/animations.cpp
	libftl/src/xml/blueprints.cpp
	libftl/src/xml/clean.cpp
	libftl/src/xml/events.cpp
	libftl/src/xml/sectors.cpp
	libftl/src/xml/ship.cpp
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

#	fcppt_utils_add_headers(
#		${LIBFTL_PARSER_FILES}
#	)

	add_library(
		${LIBFTL_LIB_NAME}
		${VARIANT}
		${LIBFTL_PARSER_FILES}
		${LIBFTL_FILES_ABS}
	)

	fcppt_utils_set_target_compiler_flags(
		${LIBFTL_LIB_NAME}
	)

	target_include_directories(
		${LIBFTL_LIB_NAME}
		PUBLIC
		${Boost_INCLUDE_DIRS}
		${Brigand_INCLUDE_DIRS}
		${FCPPT_UTILS_PROJECT_BINARY_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${XSD_INCLUDE_DIRS}
		${XercesC_INCLUDE_DIRS}
		${GENERATED_XSD_INCLUDE_DIR}
		PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/impl/include
	)

	fcppt_utils_interface_static_link(
		${LIBFTL_LIB_NAME}
		${VARIANT}
		"${LIBFTL_STATIC_LINK_FLAG}"
	)

	target_link_libraries(
		${LIBFTL_LIB_NAME}
		INTERFACE
		sgeimagecolor_interface
		sgerenderer_interface
		sgesprite_interface
		fcppt_core_interface
		fcppt_options_interface
		PRIVATE
		${Boost_FILESYSTEM_LIBRARIES}
		${XercesC_LIBRARIES}
		${sgeimagecolor_TARGET}
		${sgeimage2d_TARGET}
		${sgemedia_TARGET}
		${sgeparse_TARGET}
		${sgerenderer_TARGET}
		${sgesprite_TARGET}
		${sgetexture_TARGET}
		${alda_TARGET}
		${fcppt_core_TARGET}
		${fcppt_options_TARGET}
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
