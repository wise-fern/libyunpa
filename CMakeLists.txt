cmake_minimum_required(VERSION 4.0)
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES
    "${CMAKE_CURRENT_LIST_DIR}/cmake/TopLevel.cmake")
project(
  libyunpa
  VERSION 0.0.1
  LANGUAGES CXX)

find_package(pegtl)
add_library(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE taocpp::pegtl)
if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(
    ${PROJECT_NAME}
    PRIVATE -ggdb
            -O0
            -pedantic-errors
            -Wall
            -Wcomment
            -Wdeprecated
            -Wdocumentation
            -Weffc++
            -Wempty-body
            -Werror
            -Wextra
            -Wimplicit-fallthrough
            -Winfinite-recursion
            -Wloop-analysis
            -Wmisleading-indentation
            -Wnewline-eof
            -Wunused
            -Wparentheses)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -DNDEBUG -O3)
endif()
add_subdirectory("src")
