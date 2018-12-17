#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#

execute_process(COMMAND mc.exe -A -b -c -h . -r ${PROJECT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/eventLog.mc)

# Add the library.
add_library(winLogService
	${PROJECT_BINARY_DIR}/eventLog.h
	eventLog.mc
	logService.hpp
	logService.cpp
	win32api.hpp
)

# Add the include interface.
target_include_directories(winLogService
	PRIVATE
		${PROJECT_BINARY_DIR}
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS winLogService DESTINATION lib)
install(FILES logService.hpp DESTINATION include)
