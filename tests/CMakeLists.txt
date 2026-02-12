enable_testing()

set(
  TestsToRun
  "Point2/Equality.cpp"
)
set(tester_name libyunpa_tests)
create_test_sourcelist(TestSources ${tester_name}.cpp ${TestsToRun})

add_executable(${tester_name} ${TestSources})

foreach (test ${TestsToRun})
  get_filename_component (TName ${test} NAME_WE)
  get_filename_component (TPath ${test} DIRECTORY)
  add_test (NAME "${TPath}/${TName}" COMMAND ${tester_name} "${TPath}/${TName}")
endforeach()