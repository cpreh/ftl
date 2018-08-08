#!/bin/sh

INCLUDE_BINARY="check_includes"

find libftl programs -name include -exec "${INCLUDE_BINARY}" '{}' \; || exit
