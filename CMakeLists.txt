#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#

# Ensure minimum CMake version.
cmake_minimum_required(VERSION 3.11.1 FATAL_ERROR)

# Name the project.
project(WinLog)

# Include helper files.
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_SOURCE_DIR}/cmake/modules)

include(Compiler)
include(Defaults)

# Find prebuilt packages.
find_package(MessageCompiler REQUIRED)

# Add the library.
add_subdirectory(library)

# Add the tests (that consume the library).
add_subdirectory(tests)
