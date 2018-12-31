#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#


# Add the executable.
add_executable(test2
	main.cpp
)

# Add library dependencies.
target_link_libraries(test2
	PRIVATE
		winLogService
)

add_test(
	NAME BasicConsole
	COMMAND test2
)
