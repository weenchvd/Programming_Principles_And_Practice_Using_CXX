# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("Programming_Principles_And_Practice_Using_C++")

set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/)

# Include sub-projects.
add_subdirectory ("Chapter_02")
add_subdirectory ("Chapter_03")
add_subdirectory ("Chapter_04")
add_subdirectory ("Chapter_05")
add_subdirectory ("Chapter_06")
add_subdirectory ("Chapter_07")
add_subdirectory ("Chapter_08")
add_subdirectory ("Chapter_09")
