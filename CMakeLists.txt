cmake_minimum_required(VERSION 4.0)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)
set(CMAKE_CXX_EXTENSIONS FALSE)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
project(
    libyunpa
    VERSION 0.0.1
    LANGUAGES CXX
)

# Use ccache to cache compilation if it's available
find_program(CCACHE_EXECUTABLE ccache)
if(CCACHE_EXECUTABLE)
  message(STATUS "Found ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE} "sloppiness=modules")
endif()

# Make sure submodules are initialized and updated
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  message(STATUS "Updating submodules")
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE GIT_SUBMOD_RESULT
  )
  if(NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}. Submodules must be manually checked out.")
  endif()
endif()

set(FTXUI_BUILD_MODULES TRUE)
add_subdirectory("extern/ftxui")
add_subdirectory("src")
if(PROJECT_IS_TOP_LEVEL)
  include(CTest)
  add_subdirectory("extern/gtest")
  add_subdirectory("tests")
endif()