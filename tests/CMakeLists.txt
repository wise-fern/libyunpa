enable_testing()
include(GoogleTest)
find_package(GTest)

set(test_runner "libyunpa_tests")
add_executable(${test_runner})
target_link_libraries(
  ${test_runner}
  PRIVATE
  libyunpa
  GTest::gtest
  GTest::gtest_main
)
target_sources(
  ${test_runner}
  PRIVATE
  "System/Point2.cpp"
  "Graphics/Color.cpp"
  "Graphics/Text.cpp"
)
target_compile_features(
  ${test_runner}
  PRIVATE
  cxx_std_23
)
# target_compile_options(
#   ${test_runner}
#   PUBLIC
#   -coverage
# )
# target_link_options(
#   ${test_runner}
#   PUBLIC
#   -coverage
# )
gtest_discover_tests(${test_runner})