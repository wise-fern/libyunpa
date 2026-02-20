cmake_minimum_required(VERSION 4.0)
project(
    libyunpa
    VERSION 0.0.1
    LANGUAGES CXX
)

find_program(CCACHE_EXECUTABLE ccache)
if(CCACHE_EXECUTABLE)
  message(STATUS "Found ccache")
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_EXECUTABLE} "sloppiness=modules")
endif()

add_subdirectory("src")