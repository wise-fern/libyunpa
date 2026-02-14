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
        -ggdb -pedantic-errors
    )
    target_link_options(
        ${PROJECT_NAME}
        PRIVATE
        
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
    "libyunpa/_libyunpa.cppm"
    "libyunpa/Graphics.cppm"
    "libyunpa/System.cppm"
    PRIVATE
)