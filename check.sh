#!/bin/bash

# Run clang-format on all .h and .cpp files.

find ./src/ -iname *.h -o -iname *.cpp | xargs clang-format -i

