cmake_minimum_required(VERSION 3.14)
project(vector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable( vector_test
  vector_tests.cpp
)

target_link_libraries( vector_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector_test)

