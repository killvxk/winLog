#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#

# Add the executable.
add_executable(test1 WIN32
	main.cpp
	win32api.hpp
	window.hpp
	window.cpp
	${PROJECT_BINARY_DIR}/eventLog.rc
)

# Add library dependencies.
target_link_libraries(test1
	PRIVATE
		winLogService
)

add_test(
	NAME Basic
	COMMAND test1
)
