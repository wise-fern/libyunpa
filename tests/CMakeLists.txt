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
find_program(LLVM_COV_EXECUTABLE llvm-cov)
find_program(GCOVR_EXECUTABLE gcovr)
if(LLVM_COV_EXECUTABLE AND GCOVR_EXECUTABLE)
  message(STATUS "Found llvm-cov and gcovr. Enabling coverage reports.")
  target_link_options(
    ${TEST_RUNNER}
    PRIVATE
    -coverage
  )
  target_compile_options(
    ${TEST_RUNNER}
    PRIVATE
    -coverage
  )
  target_compile_options(
    ${PROJECT_NAME}
    PRIVATE
    -coverage
  )
  target_link_options(
    ${PROJECT_NAME}
    PRIVATE
    -coverage
  )
  set(COVERAGE_FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}_coverage.info")
  set(COVERAGE_TARGET "${PROJECT_NAME}_coverage")
  add_custom_command(
    OUTPUT ${COVERAGE_FILE}
    COMMAND ${GCOVR_EXECUTABLE} --gcov-executable "${LLVM_COV_EXECUTABLE} gcov" -r "${PROJECT_SOURCE_DIR}/src" ${PROJECT_BINARY_DIR} --lcov "${COVERAGE_FILE}"
    DEPENDS ${TEST_RUNNER}
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
  add_custom_command(
    TARGET ${TEST_RUNNER}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -f *.gcda
  )
endif()