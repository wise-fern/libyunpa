find_package(Doxygen COMPONENTS dot)
if(Doxygen_FOUND)
set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/docs)
set(DOXYGEN_HTML_COLORSTYLE "Dark")
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_CREATE_SUBDIRS YES)
doxygen_add_docs(
    ${PROJECT_NAME}_docs
    ${PROJECT_SOURCE_DIR}/docs
    ${PROJECT_SOURCE_DIR}/modules
    ALL
)
endif()