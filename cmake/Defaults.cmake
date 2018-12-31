#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#

# Ensure host compiler is C++17.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Debug builds of libraries have a different postfix to release builds.
set(CMAKE_DEBUG_POSTFIX "_d")
