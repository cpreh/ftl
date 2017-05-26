#!/bin/sh

INCLUDE_BINARY="check_includes"

find libftl -name include -exec "${INCLUDE_BINARY}" '{}' \; || exit
