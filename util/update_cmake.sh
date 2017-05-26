#!/bin/sh

set -e -u

update_cmake \
	libftl/CMakeLists.txt \
	LIBFTL_FILES \
	libftl/impl \
	libftl/include \
	libftl/src
