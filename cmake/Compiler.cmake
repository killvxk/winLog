#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#

if(MSVC)
	# Remove default warning level from CMAKE_CXX_FLAGS.
	string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	string(REGEX REPLACE "/W[0-4]" "" CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}")

	# Ensure Resource Compiler doesn't show the program banner.
	set(CMAKE_RC_FLAGS "${CMAKE_RC_FLAGS} /nologo")
	
	# Disable warnings from external headers.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /experimental:external /external:anglebrackets /external:W0")
	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   /experimental:external /external:anglebrackets /external:W0")
	
	# Highest warning level.
	add_compile_options(/W4)

	# Treat all warnings as errors.
    add_compile_options(/WX)
endif(MSVC)
