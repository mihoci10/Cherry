cmake_minimum_required(VERSION 3.4)

project(Cherry VERSION 0.1.0
             DESCRIPTION "Multipurpose, platform agnostic rendering API"
             LANGUAGES CXX)

include(FetchContent)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CHERRY_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/out CACHE STRING "Set the output base directory")
set(CHERRY_BUILD_SHARED False CACHE BOOL "Build Cherry API as a dynamic library")

set(CHERRY_ENABLE_OPENGL True CACHE BOOL "Build the OpenGL platform")
set(CHERRY_ENABLE_IMGUI False CACHE BOOL "Include the ImGui functionality")

# set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CHERRY_OUT_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CHERRY_OUT_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CHERRY_OUT_DIR}/bin)

# auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()

# detect platform
if(WIN32)
  set(CHERRY_PLATFORM_WIN True BOOL)
endif()
if(UNIX)
  set(CHERRY_PLATFORM_UNIX True BOOL)
endif()

function(defineBoolVariable varName)
  set(varValue "${${varName}}")
  if(varValue)
    add_compile_definitions(${varName})
  endif()
endfunction()

function(collectSources varName dir)
  file(GLOB SOURCES "${dir}/*.c" "${dir}/*.cpp" "${dir}/*.h" "${dir}/*.hpp")
  set("${varName}" "${SOURCES}" PARENT_SCOPE)
endfunction()

defineBoolVariable(CHERRY_PLATFORM_WIN)
defineBoolVariable(CHERRY_BUILD_SHARED)

add_subdirectory(CherryAPI)
add_subdirectory(CherryExample)