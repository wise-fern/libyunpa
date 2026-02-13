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
target_sources(
    ${PROJECT_NAME}
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    "src/libyunpa/_libyunpa.cppm"
    "src/libyunpa/Graphics.cppm"
    "src/libyunpa/System.cppm"
)
enable_testing()
add_subdirectory("tests")
