#!/bin/sh

set -e -u

update_cmake.sh \
	libftl/files.txt \
	libftl/impl \
	libftl/include \
	libftl/src

update_cmake.sh \
	programs/parse/files.txt \
	programs/parse/include \
	programs/parse/src
