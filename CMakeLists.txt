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
add_subdirectory("modules")
add_subdirectory("docs")
