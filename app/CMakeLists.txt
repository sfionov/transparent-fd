cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(native-lib SHARED src/main/cpp/native-lib.cpp)

set(CMAKE_EXE_C_FLAGS "${ANDROID_C_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${ANDROID_LINKER_FLAGS}")
add_executable(create_transparent_socket_sdk15 src/main/cpp/create_transparent_socket.c)
set_property(TARGET create_transparent_socket_sdk15 PROPERTY POSITION_INDEPENDENT_CODE FALSE)
add_executable(create_transparent_socket_sdk16pie src/main/cpp/create_transparent_socket.c)
set_property(TARGET create_transparent_socket_sdk16pie PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_property(TARGET create_transparent_socket_sdk16pie PROPERTY LINK_FLAGS "-fPIE -pie")

# Install ARM binaries to assets
if(ANDROID_ABI STREQUAL "armeabi-v7a")
set_property(TARGET create_transparent_socket_sdk15 PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/main/assets")
set_property(TARGET create_transparent_socket_sdk16pie PROPERTY RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/main/assets")
endif()
