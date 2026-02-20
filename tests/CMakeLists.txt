set(TEST_RUNNER "${PROJECT_NAME}_tester")
add_executable(${TEST_RUNNER})
set_target_properties(
  ${TEST_RUNNER}
  PROPERTIES
  FOLDER "${PROJECT_NAME}"
  CXX_STANDARD 23
  CXX_EXTENSIONS FALSE
  CXX_MODULE_STD TRUE
)
target_link_libraries(
  ${TEST_RUNNER}
  PRIVATE
  libyunpa
  GTest::gmock_main
)
target_sources(
  ${TEST_RUNNER}
  PRIVATE
  "System/Clock.cpp"
)
include(GoogleTest)
gtest_discover_tests(${TEST_RUNNER})
find_program(LLVM_PROFDATA_EXECUTABLE llvm-profdata)
find_program(LLVM_COV_EXECUTABLE llvm-cov)
if(LLVM_PROFDATA_EXECUTABLE AND LLVM_COV_EXECUTABLE)
  message(STATUS "Found llvm-cov and llvm-profdata. Enabling coverage reports.")
  target_link_options(
    ${TEST_RUNNER}
    PRIVATE
    -fprofile-instr-generate
  )
  target_compile_options(
    ${TEST_RUNNER}
    PRIVATE
    -fprofile-instr-generate #-fcoverage-mapping
  )
  target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -fprofile-instr-generate -fcoverage-mapping
  )
  target_link_options(
    ${PROJECT_NAME}
    PRIVATE
    -fprofile-instr-generate
  )
  set(PROFRAW_FILE "${CMAKE_CURRENT_BINARY_DIR}/default.profraw")
  set(COVERAGE_FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_coverage.info")
  set(PROFDATA_FILE "${CMAKE_CURRENT_BINARY_DIR}/default.profdata")
  set(COVERAGE_TARGET "${PROJECT_NAME}_coverage")
  add_custom_command(
    OUTPUT ${PROFDATA_FILE}
    COMMAND ${TEST_RUNNER}
    COMMAND ${LLVM_PROFDATA_EXECUTABLE} merge -sparse "${PROFRAW_FILE}" -o "${PROFDATA_FILE}"
    DEPENDS ${TEST_RUNNER}
  )
  add_custom_command(
    OUTPUT ${COVERAGE_FILE}
    COMMAND ${LLVM_COV_EXECUTABLE} export ${TEST_RUNNER} --sources="${ABSOLUTE_SOURCES}" --format=lcov -instr-profile="${PROFDATA_FILE}" > "${COVERAGE_FILE}"
    DEPENDS ${PROFDATA_FILE}
  )
  add_custom_target(
    ${COVERAGE_TARGET}
    DEPENDS ${COVERAGE_FILE}
  )
  set_target_properties(
    ${COVERAGE_TARGET}
    PROPERTIES
    FOLDER ${PROJECT_NAME}
  )
endif()