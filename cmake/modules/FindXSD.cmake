find_path(
	XSD_INCLUDE_DIR
	xsd
	HINTS
	"${XSD_INCLUDEDIR}"
)

find_program(
	XSD_PROGRAM
	xsdcxx
	HINTS
	"${XSD_PROGRAMDIR}"
)

include(
	FindPackageHandleStandardArgs
)

find_package_handle_standard_args(
	XSD
	DEFAULT_MSG
	XSD_PROGRAM
	XSD_INCLUDE_DIR
)

if(
	XSD_FOUND
)
	set(
		XSD_INCLUDE_DIRS
		"${XSD_INCLUDE_DIR}"
	)
endif()

mark_as_advanced(
	XSD_INCLUDE_DIR
)
