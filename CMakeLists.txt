cmake_minimum_required(VERSION 2.8)
project(SILHOUETTE CXX)
set(SILHOUETTE_MAJOR_VERSION 0)
set(SILHOUETTE_MINOR_VERSION 1)
set(SILHOUETTE_PATCH_VERSION 0)

# We use delegated constructors so we must use c++11 or greater
add_definitions("-std=c++11")

enable_testing()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/SilhouetteConfig.h.in"
  "${PROJECT_BINARY_DIR}/SilhouetteConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# for making our library
add_subdirectory(${SILHOUETTE_SOURCE_DIR}/src)

# for the header files
add_subdirectory(${SILHOUETTE_SOURCE_DIR}/include)

# for making the tests
add_subdirectory(${SILHOUETTE_SOURCE_DIR}/tests)
set(CMAKE_INCLUDE_PATH ./)

