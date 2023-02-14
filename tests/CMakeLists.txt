cmake_minimum_required(VERSION 3.5.1)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Gtest REQUIRED gtest)

include_directories(
  ${Gtest_INCLUDE_DIRS}
)

link_directories (
  ${Gtest_LIBRARY_DIRS}
)

SET(TEST_SOURCES
  macros_test
)

FOREACH(test_src ${TEST_SOURCES})
  add_executable(${test_src} ${test_src}.cc)
  target_link_libraries(${test_src}
    ${TARGET_NAME}
    ${Gtest_LIBRARIES}
    gtest
  )
ENDFOREACH(test_src)
