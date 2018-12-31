#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#

# Add command to build the resource files.
set(SYSLOG_SRCS ${CMAKE_CURRENT_BINARY_DIR}/eventLog.h)

set_source_files_properties(${SYSLOG_SRCS} PROPERTIES GENERATED TRUE)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/eventLog.rc
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/eventLog.mc
    COMMAND ${CMAKE_MC_COMPILER} -A -b -c -h . -r ${CMAKE_CURRENT_BINARY_DIR} eventLog.mc
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/eventLog.rc PROPERTIES GENERATED TRUE)

# Add the library.
add_library(winLogService
	${CMAKE_CURRENT_BINARY_DIR}/eventLog.h
	${CMAKE_CURRENT_BINARY_DIR}/eventLog.rc
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
