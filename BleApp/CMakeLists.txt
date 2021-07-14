#Copy this file to the application project folder as CMakeLists.txt
cmake_minimum_required (VERSION 3.6)

# Grab the SDK location
if(NOT DEFINED SOS_SDK_PATH)
	if(DEFINED ENV{SOS_SDK_PATH})
		set(SOS_SDK_PATH $ENV{SOS_SDK_PATH})
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH /Applications/StratifyLabs-SDK)
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH C:/StratifyLabs-SDK)
	elseif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )
		message(WARNING "default SDK locations are deprecated")
		set(SOS_SDK_PATH /StratifyLabs-SDK)
	endif()
endif()
if(NOT DEFINED SOS_SDK_PATH)
	message(FATAL_ERROR "Please set environment variable SOS_SDK_PATH to location of the StratifyLabs-SDK directory")
endif()
set(SOS_TOOLCHAIN_CMAKE_PATH ${SOS_SDK_PATH}/Tools/gcc/arm-none-eabi/cmake)

include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-variables.cmake)
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-sdk.cmake)

# Override standard SOS variables here
if( ${SOS_BUILD_CONFIG} STREQUAL arm )
	set(CMAKE_TOOLCHAIN_FILE ${SOS_TOOLCHAIN_CMAKE_PATH}/sos-app-toolchain.cmake)
elseif( ${SOS_BUILD_CONFIG} STREQUAL link )
	set(CMAKE_TOOLCHAIN_FILE ${SOS_TOOLCHAIN_CMAKE_PATH}/link-toolchain.cmake)
endif()

# This will set the default RAM used by the application
set(SOS_RAM_SIZE 4096)

#Add sources to the project
sos_sdk_add_subdirectory(SOS_SOURCELIST ${CMAKE_SOURCE_DIR}/src)
list(
	APPEND
	SOS_SOURCELIST
	${SOURCES}
	${CMAKE_SOURCE_DIR}/sl_settings.json
	${CMAKE_SOURCE_DIR}/README.md)

get_filename_component(SOS_NAME ${CMAKE_SOURCE_DIR} NAME)
project(${SOS_NAME} CXX C)

set(BLE_API_PATH ${CMAKE_SOURCE_DIR}/..)
set(BLE_INCLUDE_DIRECTORIES
	${BLE_API_PATH}/stacks/ble-host/include
	${BLE_API_PATH}/stacks/ble-profiles/include
	${BLE_API_PATH}/stacks/ble-profiles/sources/services
	${BLE_API_PATH}/stacks/ble-profiles/sources/profiles
	${BLE_API_PATH}/stacks/ble-profiles/sources/af
	${BLE_API_PATH}/stacks/ble-host/sources/hci/dual_chip
	${BLE_API_PATH}/stacks/ble-host/sources/hci/dual_chip
	${BLE_API_PATH}/porting/cfg
	${BLE_API_PATH}/stacks/ble-apps/sources/datc
	${BLE_API_PATH}/stacks/ble-apps/sources
	${BLE_API_PATH}/stacks/wsf/include

	)

SET(SOS_DEFINITIONS
	WSF_TRACE_ENABLED=1
	WSF_TOKEN_ENABLED=1
	MODULE_ID=4
	WSF_ASSERT_ENABLED=1
	)


if( ${SOS_BUILD_CONFIG} STREQUAL arm )
	#This will cross compile for all supported ARM architetures
	set(SOS_BUILD_FLAGS -fprofile-arcs -ftest-coverage)
	#set(SOS_LIBRARIES -L${BLE_API_PATH}/cmake_arm BleAPI)

	include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-app-std.cmake)
elseif( ${SOS_BUILD_CONFIG} STREQUAL link )
	#This will compile natively. If the program uses hardware, it can "link" to a board over USB
	set(SOS_LIBRARIES -L${BLE_API_PATH}/cmake_link BleAPI_link)
	list(APPEND SOS_INCLUDE_DIRECTORIES ${BLE_INCLUDE_DIRECTORIES})
	set(SOS_ARCH link)
	set(SOS_CONFIG release)
	include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-app.cmake)
endif()
