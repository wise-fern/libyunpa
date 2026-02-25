include(FetchContent)
FetchContent_Declare(
  pegtl
  GIT_REPOSITORY https://github.com/taocpp/pegtl.git
  GIT_TAG 3.2.8
  GIT_SHALLOW TRUE
  SYSTEM EXCLUDE_FROM_ALL OVERRIDE_FIND_PACKAGE)
