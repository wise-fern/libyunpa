cmake_minimum_required(VERSION 4.0)
project(
  libyunpa
  VERSION 0.0.1
  LANGUAGES CXX)
add_library(${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" FOLDER
                                                           ${PROJECT_NAME})
if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32=1)
endif()
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE pegtl
  PUBLIC ftxui::modules)
target_compile_options(
  ${PROJECT_NAME}
  PRIVATE -O0
          -ggdb
          -fmodules-reduced-bmi
          -Wall
          -Wconversion
          -Wdecls-in-multiple-modules
          -Weffc++
          -Werror
          -Wextra
          -Wimplicit-fallthrough
          -Wloop-analysis
          -Wnewline-eof
          -Wparentheses
          -Wpessimizing-move
          -Wredundant-move
          -Wself-move
          -Wsign-conversion
          -Wsuggest-override
          -Wsuper-class-method-mismatch
          -Wtautological-compare
          -Wthread-safety
          -Wunreachable-code-aggressive
          -Wunused
          -Wused-but-marked-unused)
add_subdirectory("src")
