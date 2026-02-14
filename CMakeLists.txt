cmake_minimum_required(VERSION 4.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)
set(CMAKE_MODULE_STD YES)
option(LIBYUNPA_BUILD_TESTS "Whether to build libyunpa's tests" OFF)
set(LIBYUNPA_BUILD_TESTS ON)
project(
    libyunpa
    VERSION 0.0.1
    LANGUAGES CXX
)
add_subdirectory("src")

if(LIBYUNPA_BUILD_TESTS)
include(CTest)
enable_testing()
add_subdirectory("tests")
endif()
