cmake_minimum_required(VERSION 4.0)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)
set(CMAKE_MODULE_STD YES)
project(
    libyunpa
    VERSION 0.0.1
    LANGUAGES CXX
)

add_library(${PROJECT_NAME})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_MODULE_STD YES
    CXX_STANDARD 23
)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        -ggdb
    )
else()
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        -O3 -DNDEBUG
    )
endif()
target_sources(
    ${PROJECT_NAME}
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    "src/libyunpa/_libyunpa.cppm"
    "src/libyunpa/Graphics.cppm"
    "src/libyunpa/System.cppm"
    PRIVATE
)
enable_testing()
add_subdirectory("tests")
