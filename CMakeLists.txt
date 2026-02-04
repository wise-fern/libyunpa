cmake_minimum_required(VERSION 3.28)
project(
    libyunpa
    VERSION 0.4.0.0
    DESCRIPTION "A library to help with Young Pastry"
    LANGUAGES CXX
)
add_library(${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY PREFIX "")
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    pegtl
    PUBLIC
    ftxui::modules
)
target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -Wall -Wextra -Weffc++
    -Wconversion -pedantic-errors
    -Wsign-conversion -Werror
)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -ggdb -ggdb3
)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -O3 -DNDEBUG
)
endif()
add_subdirectory("modules")
# add_subdirectory("docs")
