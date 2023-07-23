cmake_minimum_required(VERSION 3.5.1)
project(cactus VERSION 1.2.1)

set(TARGET_NAME ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug) # Debug Release

option(BUILD_SHARED_LIBS "Build cactus shared library" ON)
option(BUILD_CACTUS_TEST "Build cactus unittest" OFF)

set(CACTUS_SHARED_TYPE SHARED)
if (NOT BUILD_SHARED_LIBS)
  set(CACTUS_SHARED_TYPE STATIC)
endif()

message("####### option shared type:${CACTUS_SHARED_TYPE}")
message("####### option unittest:${BUILD_CACTUS_TEST}")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(PkgConfig REQUIRED)

include_directories(
  include
)

file(GLOB CACTUS_SRCS
  "src/*.cc"
)

add_library(${TARGET_NAME} ${CACTUS_SHARED_TYPE}
  ${CACTUS_SRCS}
)

if(BUILD_CACTUS_TEST)
  add_subdirectory(tests)
endif(BUILD_CACTUS_TEST)

# #################################################################################
# version
# #################################################################################
configure_file(include/${PROJECT_NAME}/version.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/version.h
)

# #################################################################################
# config
# #################################################################################
configure_file("cmake/${TARGET_NAME}.pc.in"
  "${PROJECT_BINARY_DIR}/pkgconfig/${TARGET_NAME}.pc" @ONLY)

configure_package_config_file(
  "cmake/${TARGET_NAME}-config.cmake.in"
  "${PROJECT_BINARY_DIR}/cmake/${TARGET_NAME}-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${TARGET_NAME}"
  PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
)

write_basic_package_version_file(
  "cmake/${TARGET_NAME}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  "${PROJECT_BINARY_DIR}/pkgconfig/${TARGET_NAME}.pc"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/pkgconfig"
)

install(EXPORT ${TARGET_NAME}-targets
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${TARGET_NAME}"
)

install(FILES
  "${PROJECT_BINARY_DIR}/cmake/${TARGET_NAME}-config.cmake"
  "${PROJECT_BINARY_DIR}/cmake/${TARGET_NAME}-config-version.cmake"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/cmake/${TARGET_NAME}"
)

install(DIRECTORY include/${TARGET_NAME}/
  DESTINATION include/${TARGET_NAME}
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "*.hpp"
)

install(TARGETS ${TARGET_NAME}
  EXPORT ${TARGET_NAME}-targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
