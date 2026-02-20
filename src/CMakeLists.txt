add_library(${PROJECT_NAME})
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES
  PREFIX ""
  FOLDER "${PROJECT_NAME}"
  CXX_STANDARD 23
  CXX_STANDARD_REQUIRED TRUE
  CXX_EXTENSIONS FALSE
  CXX_MODULE_STD TRUE
)
if(WIN32)
  target_compile_definitions(
    ${PROJECT_NAME}
    PRIVATE
    WIN32
  )
endif()
set(
  RELATIVE_SOURCES
  "libyunpa.cppm"
  "Engine/Scene.cppm"
  "System/Events.cppm"
  "System/Time.cppm"
)
foreach(source_file IN LISTS RELATIVE_SOURCES)
  list(APPEND ABSOLUTE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${source_file}")
endforeach()
set(ABSOLUTE_SOURCES PARENT_SCOPE)
target_sources(
  ${PROJECT_NAME}
  PUBLIC
  FILE_SET CXX_MODULES
  FILES
  ${ABSOLUTE_SOURCES}
)
target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  ftxui::modules
)