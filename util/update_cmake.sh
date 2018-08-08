#!/bin/sh

set -e -u

update_cmake \
	libftl/CMakeLists.txt \
	LIBFTL_FILES \
	libftl/impl \
	libftl/include \
	libftl/src

update_cmake \
	programs/parse/CMakeLists.txt \
	FTLPARSE_FILES \
	programs/parse/include \
	programs/parse/src
