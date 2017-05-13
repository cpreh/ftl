#!/bin/sh

set -e -u

update_cmake \
	libftl/CMakeLists.txt \
	LIBFTL_FILES \
	libftl/include \
	libftl/src
