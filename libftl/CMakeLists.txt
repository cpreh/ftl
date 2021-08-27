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
	renderer
	sprite
	texture
)

find_package(
	XercesC
	REQUIRED
)

find_package(
	XSD
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
			--cxx-prologue
			"#include <fcppt/config/external_begin.hpp>"
			--cxx-epilogue
			"#include <fcppt/config/external_end.hpp>"
			--fwd-prologue
			"#include <fcppt/config/external_begin.hpp>"
			--fwd-epilogue
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
	animations
	blueprints
	events
	sectors
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
	libftl/impl/include/libftl/impl/blueprints/find.hpp
	libftl/impl/include/libftl/impl/room/draw.hpp
	libftl/impl/include/libftl/impl/xml/attribute.hpp
	libftl/impl/include/libftl/impl/xml/attribute_fwd.hpp
	libftl/impl/include/libftl/impl/xml/document.hpp
	libftl/impl/include/libftl/impl/xml/document_fwd.hpp
	libftl/impl/include/libftl/impl/xml/document_output.hpp
	libftl/impl/include/libftl/impl/xml/file_to_string.hpp
	libftl/impl/include/libftl/impl/xml/inner_node.hpp
	libftl/impl/include/libftl/impl/xml/inner_node_content.hpp
	libftl/impl/include/libftl/impl/xml/inner_node_fwd.hpp
	libftl/impl/include/libftl/impl/xml/load_function.hpp
	libftl/impl/include/libftl/impl/xml/make_load_function.hpp
	libftl/impl/include/libftl/impl/xml/node.hpp
	libftl/impl/include/libftl/impl/xml/node_fwd.hpp
	libftl/impl/include/libftl/impl/xml/node_vector.hpp
	libftl/impl/include/libftl/impl/xml/output.hpp
	libftl/impl/include/libftl/impl/xml/parse.hpp
	libftl/impl/include/libftl/impl/xml/read.hpp
	libftl/impl/include/libftl/impl/xml/remove_comments.hpp
	libftl/impl/include/libftl/impl/xml/typed/attribute.hpp
	libftl/impl/include/libftl/impl/xml/typed/attribute_fwd.hpp
	libftl/impl/include/libftl/impl/xml/typed/attribute_set.hpp
	libftl/impl/include/libftl/impl/xml/typed/basic_set.hpp
	libftl/impl/include/libftl/impl/xml/typed/content.hpp
	libftl/impl/include/libftl/impl/xml/typed/empty.hpp
	libftl/impl/include/libftl/impl/xml/typed/inner_node.hpp
	libftl/impl/include/libftl/impl/xml/typed/is_attribute.hpp
	libftl/impl/include/libftl/impl/xml/typed/is_node_member.hpp
	libftl/impl/include/libftl/impl/xml/typed/make_node_member.hpp
	libftl/impl/include/libftl/impl/xml/typed/node.hpp
	libftl/impl/include/libftl/impl/xml/typed/node_list.hpp
	libftl/impl/include/libftl/impl/xml/typed/node_member.hpp
	libftl/impl/include/libftl/impl/xml/typed/node_member_fwd.hpp
	libftl/impl/include/libftl/impl/xml/typed/node_set.hpp
	libftl/impl/include/libftl/impl/xml/typed/parses.hpp
	libftl/impl/include/libftl/impl/xml/typed/required.hpp
	libftl/impl/include/libftl/impl/xml/typed/result_type.hpp
	libftl/impl/include/libftl/impl/xsd/require_one.hpp
	libftl/impl/include/libftl/impl/xsd/to_fcppt_optional.hpp
	libftl/impl/src/impl/archive/chain.cpp
	libftl/impl/src/impl/archive/filesystem.cpp
	libftl/impl/src/impl/archive/native.cpp
	libftl/impl/src/impl/room/draw.cpp
	libftl/impl/src/impl/xml/document_output.cpp
	libftl/impl/src/impl/xml/file_to_string.cpp
	libftl/impl/src/impl/xml/output.cpp
	libftl/impl/src/impl/xml/parse.cpp
	libftl/impl/src/impl/xml/remove_comments.cpp
	libftl/include/libftl/archive/base.hpp
	libftl/include/libftl/archive/base_fwd.hpp
	libftl/include/libftl/archive/base_ref.hpp
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
	libftl/include/libftl/blueprints/data.hpp
	libftl/include/libftl/blueprints/data_fwd.hpp
	libftl/include/libftl/blueprints/find_ship.hpp
	libftl/include/libftl/blueprints/load.hpp
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
	libftl/include/libftl/room/state.hpp
	libftl/include/libftl/room/state_fwd.hpp
	libftl/include/libftl/room/system.hpp
	libftl/include/libftl/room/system_fwd.hpp
	libftl/include/libftl/room/type.hpp
	libftl/include/libftl/room/type_fwd.hpp
	libftl/include/libftl/ship/draw.hpp
	libftl/include/libftl/ship/images/load.hpp
	libftl/include/libftl/ship/images/name.hpp
	libftl/include/libftl/ship/images/name_fwd.hpp
	libftl/include/libftl/ship/images/object.hpp
	libftl/include/libftl/ship/images/object_fwd.hpp
	libftl/include/libftl/ship/initial_state.hpp
	libftl/include/libftl/ship/layout/door.hpp
	libftl/include/libftl/ship/layout/door_fwd.hpp
	libftl/include/libftl/ship/layout/ellipse.hpp
	libftl/include/libftl/ship/layout/ellipse_fwd.hpp
	libftl/include/libftl/ship/layout/load.hpp
	libftl/include/libftl/ship/layout/load_xml.hpp
	libftl/include/libftl/ship/layout/name.hpp
	libftl/include/libftl/ship/layout/name_fwd.hpp
	libftl/include/libftl/ship/layout/object.hpp
	libftl/include/libftl/ship/layout/object_fwd.hpp
	libftl/include/libftl/ship/layout/output.hpp
	libftl/include/libftl/ship/layout/parse.hpp
	libftl/include/libftl/ship/layout/room.hpp
	libftl/include/libftl/ship/layout/room_fwd.hpp
	libftl/include/libftl/ship/layout/room_id.hpp
	libftl/include/libftl/ship/layout/tile_coordinate.hpp
	libftl/include/libftl/ship/layout/tile_pos.hpp
	libftl/include/libftl/ship/layout/tile_pos_fwd.hpp
	libftl/include/libftl/ship/layout/tile_rect.hpp
	libftl/include/libftl/ship/layout/tile_rect_fwd.hpp
	libftl/include/libftl/ship/load.hpp
	libftl/include/libftl/ship/resources.hpp
	libftl/include/libftl/ship/resources_fwd.hpp
	libftl/include/libftl/ship/state.hpp
	libftl/include/libftl/ship/state_fwd.hpp
	libftl/include/libftl/sprite/choices.hpp
	libftl/include/libftl/sprite/choices_fwd.hpp
	libftl/include/libftl/sprite/color.hpp
	libftl/include/libftl/sprite/color_format.hpp
	libftl/include/libftl/sprite/color_fwd.hpp
	libftl/include/libftl/sprite/depth.hpp
	libftl/include/libftl/sprite/depth_fwd.hpp
	libftl/include/libftl/sprite/depth_role.hpp
	libftl/include/libftl/sprite/detail/depth_element.hpp
	libftl/include/libftl/sprite/detail/depth_element_fwd.hpp
	libftl/include/libftl/sprite/draw.hpp
	libftl/include/libftl/sprite/images.hpp
	libftl/include/libftl/sprite/images_fwd.hpp
	libftl/include/libftl/sprite/object.hpp
	libftl/include/libftl/sprite/object_fwd.hpp
	libftl/include/libftl/sprite/rect.hpp
	libftl/include/libftl/sprite/rect_fwd.hpp
	libftl/include/libftl/sprite/resolution.hpp
	libftl/include/libftl/sprite/size_or_texture_size.hpp
	libftl/include/libftl/sprite/size_or_texture_size_fwd.hpp
	libftl/include/libftl/sprite/type_choices.hpp
	libftl/include/libftl/sprite/type_choices_fwd.hpp
	libftl/include/libftl/sprite/white.hpp
	libftl/include/libftl/xml/achievements.hpp
	libftl/include/libftl/xml/achievements_result.hpp
	libftl/include/libftl/xml/animations.hpp
	libftl/include/libftl/xml/blueprints.hpp
	libftl/include/libftl/xml/clean.hpp
	libftl/include/libftl/xml/events.hpp
	libftl/include/libftl/xml/labels/angular.hpp
	libftl/include/libftl/xml/labels/cloak.hpp
	libftl/include/libftl/xml/labels/desc.hpp
	libftl/include/libftl/xml/labels/direction.hpp
	libftl/include/libftl/xml/labels/explosion.hpp
	libftl/include/libftl/xml/labels/floor.hpp
	libftl/include/libftl/xml/labels/gib.hpp
	libftl/include/libftl/xml/labels/gib1.hpp
	libftl/include/libftl/xml/labels/gib2.hpp
	libftl/include/libftl/xml/labels/gib3.hpp
	libftl/include/libftl/xml/labels/gib4.hpp
	libftl/include/libftl/xml/labels/gib5.hpp
	libftl/include/libftl/xml/labels/gib6.hpp
	libftl/include/libftl/xml/labels/glow_offset.hpp
	libftl/include/libftl/xml/labels/h.hpp
	libftl/include/libftl/xml/labels/id.hpp
	libftl/include/libftl/xml/labels/img.hpp
	libftl/include/libftl/xml/labels/max.hpp
	libftl/include/libftl/xml/labels/min.hpp
	libftl/include/libftl/xml/labels/mirror.hpp
	libftl/include/libftl/xml/labels/multi_difficulty.hpp
	libftl/include/libftl/xml/labels/name.hpp
	libftl/include/libftl/xml/labels/offsets.hpp
	libftl/include/libftl/xml/labels/rotate.hpp
	libftl/include/libftl/xml/labels/ship.hpp
	libftl/include/libftl/xml/labels/slide.hpp
	libftl/include/libftl/xml/labels/velocity.hpp
	libftl/include/libftl/xml/labels/w.hpp
	libftl/include/libftl/xml/labels/weapon_mounts.hpp
	libftl/include/libftl/xml/labels/x.hpp
	libftl/include/libftl/xml/labels/y.hpp
	libftl/include/libftl/xml/node.hpp
	libftl/include/libftl/xml/node_output.hpp
	libftl/include/libftl/xml/sectors.hpp
	libftl/include/libftl/xml/ship/explosion.hpp
	libftl/include/libftl/xml/ship/gib.hpp
	libftl/include/libftl/xml/ship/img.hpp
	libftl/include/libftl/xml/ship/load.hpp
	libftl/include/libftl/xml/ship/offset.hpp
	libftl/include/libftl/xml/ship/offsets.hpp
	libftl/include/libftl/xml/ship/result.hpp
	libftl/include/libftl/xml/ship/slide.hpp
	libftl/include/libftl/xml/ship/slide_input.hpp
	libftl/include/libftl/xml/ship/slide_output.hpp
	libftl/include/libftl/xml/ship/slide_to_string.hpp
	libftl/src/archive/base.cpp
	libftl/src/archive/chain.cpp
	libftl/src/archive/entry_output.cpp
	libftl/src/archive/extract.cpp
	libftl/src/archive/filesystem.cpp
	libftl/src/archive/open.cpp
	libftl/src/archive/path.cpp
	libftl/src/archive/read_index.cpp
	libftl/src/blueprints/data.cpp
	libftl/src/blueprints/find_ship.cpp
	libftl/src/blueprints/load.cpp
	libftl/src/options/create_resource_parser.cpp
	libftl/src/options/open_archive.cpp
	libftl/src/room/state.cpp
	libftl/src/room/system.cpp
	libftl/src/ship/draw.cpp
	libftl/src/ship/images/load.cpp
	libftl/src/ship/images/object.cpp
	libftl/src/ship/initial_state.cpp
	libftl/src/ship/layout/load.cpp
	libftl/src/ship/layout/load_xml.cpp
	libftl/src/ship/layout/object.cpp
	libftl/src/ship/layout/output.cpp
	libftl/src/ship/layout/parse.cpp
	libftl/src/ship/load.cpp
	libftl/src/ship/resources.cpp
	libftl/src/ship/state.cpp
	libftl/src/sprite/draw.cpp
	libftl/src/sprite/images.cpp
	libftl/src/sprite/resolution.cpp
	libftl/src/sprite/white.cpp
	libftl/src/xml/achievements.cpp
	libftl/src/xml/animations.cpp
	libftl/src/xml/blueprints.cpp
	libftl/src/xml/clean.cpp
	libftl/src/xml/events.cpp
	libftl/src/xml/sectors.cpp
	libftl/src/xml/ship/load.cpp
	libftl/src/xml/ship/slide_to_string.cpp
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
	if(${VARIANT} STREQUAL "STATIC")
		fcppt_utils_static_link_name(
			libftl
			LIBFTL_LIB_NAME
		)
	elseif(${VARIANT} STREQUAL "INTERFACE")
		fcppt_utils_interface_link_name(
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

	if(${VARIANT} STREQUAL "INTERFACE")
		add_library(
			${LIBFTL_LIB_NAME}
			${VARIANT}
		)
	else()
		add_library(
			${LIBFTL_LIB_NAME}
			${VARIANT}
			${LIBFTL_PARSER_FILES}
			${LIBFTL_FILES_ABS}
		)
	endif()

	if(NOT ${VARIANT} STREQUAL "INTERFACE")
		fcppt_utils_set_target_compiler_flags(
			${LIBFTL_LIB_NAME}
		)
	endif()

	target_include_directories(
		${LIBFTL_LIB_NAME}
		INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/include
	)

	if(NOT ${VARIANT} STREQUAL "INTERFACE")
		target_include_directories(
			${LIBFTL_LIB_NAME}
			PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/include
			${CMAKE_CURRENT_SOURCE_DIR}/impl/include
		)
	endif()

	target_include_directories(
		${LIBFTL_LIB_NAME}
		SYSTEM
		INTERFACE
		${FCPPT_UTILS_PROJECT_BINARY_DIR}/include
		${XSD_INCLUDE_DIRS}
		${XercesC_INCLUDE_DIRS}
		${GENERATED_XSD_INCLUDE_DIR}
	)

	if(NOT ${VARIANT} STREQUAL "INTERFACE")
		target_include_directories(
			${LIBFTL_LIB_NAME}
			SYSTEM
			PRIVATE
			${FCPPT_UTILS_PROJECT_BINARY_DIR}/include
			${XSD_INCLUDE_DIRS}
			${XercesC_INCLUDE_DIRS}
			${GENERATED_XSD_INCLUDE_DIR}
		)
	endif()

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
	)

	if(NOT ${VARIANT} STREQUAL "INTERFACE")
		target_link_libraries(
			${LIBFTL_LIB_NAME}
			PRIVATE
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
			fcppt_parse_interface
		)
	endif()

	target_compile_definitions(
		${LIBFTL_LIB_NAME}
		INTERFACE
		XSD_CXX11
		_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR
	)

	if(NOT ${VARIANT} STREQUAL "INTERFACE")
		target_compile_definitions(
			${LIBFTL_LIB_NAME}
			PRIVATE
			XSD_CXX11
			_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR
		)
	endif()

	add_dependencies(
		${LIBFTL_LIB_NAME}
		xsdfiles
	)

	fcppt_utils_export_install_target(
		${LIBFTL_LIB_NAME}
	)
endfunction()

if(ENABLE_SHARED)
	add_libftl_library(
		"SHARED"
	)
endif()

if(ENABLE_STATIC)
	add_libftl_library(
		"STATIC"
	)
endif()

add_libftl_library(
	"INTERFACE"
)

add_library(
	libftl_impl_interface
	INTERFACE
)

target_include_directories(
	libftl_impl_interface
	INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/impl/include
)

target_link_libraries(
	libftl_impl_interface
	INTERFACE
	libftl_interface
)
