#
# Copyright (c) 2018 Jamie Kenyon. All Rights Reserved.
#

if(WIN32)
	include(FindPackageHandleStandardArgs)

	set(WIN10_REG_KEY "[HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0;")

	# Find the Windows SDK version.
	get_filename_component(WIN10_SDK_VERSION "${WIN10_REG_KEY}ProductVersion]" ABSOLUTE CACHE)
	get_filename_component(WIN10_SDK_VERSION ${WIN10_SDK_VERSION} NAME)

	# Find the Windoes SDK path.
	get_filename_component(WIN10_SDK_PATH "${WIN_REG_KEY};InstallationFolder]" ABSOLUTE CACHE)
	if(IS_DIRECTORY "${WIN10_SDK_PATH}/bin/${WIN10_SDK_VERSION}.0/x64")
		set(WIN10_SDK_VERSION "${WIN10_SDK_VERSION}.0")
	endif()

	set(WIN10_BIN_PATH "${WIN10_SDK_PATH}/bin/${WIN10_SDK_VERSION}/x64")

	find_program(CMAKE_MC_COMPILER mc.exe
		HINTS "${WIN10_BIN_PATH}"
		DOC "Path to message compiler"
	)
	
	if(NOT CMAKE_MC_COMPILER)
		message(FATAL_ERROR "message compiler not found: required to build")
	endif()
endif(WIN32)
