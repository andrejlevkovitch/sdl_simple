#cmake

cmake_minimum_required(VERSION 3.5)

project(sdl_simple)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(copy_commands ALL COMMAND
  cp "${CMAKE_BINARY_DIR}/compile_commands.json" "${CMAKE_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

set(LIST_TARGETS CACHE STRING "list of targets" FORCE)
set(LIST_SUBDIRS sdl_model sdl_view main)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")

set(CONFIG_DIR "${CMAKE_BINARY_DIR}/include")
set(CONFIG_H "${CONFIG_DIR}/config.h")
configure_file("config.h.cmake" ${CONFIG_H})

include_directories(${CONFIG_DIR})

include(build.cmake)

message(STATUS "SUBDIRECTORIES: ${LIST_SUBDIRS}")
message(STATUS "TARGETS: ${LIST_TARGETS}")
