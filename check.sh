#!/bin/bash

# Run clang-format on all .h and .cpp files.

find ./src/ -iname "*.h" -print0 -o -iname "*.cpp"  | xargs -0 clang-format -i

