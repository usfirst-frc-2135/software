#!/bin/sh
set -eux
if command -v cygpath; then
    npx clang-format -i "$(realpath --relative-to=. "$(cygpath "$@")")"
else
    npx clang-format -i $@
fi