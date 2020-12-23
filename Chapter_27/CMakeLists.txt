# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_27")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_C_STANDARD 99)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)

# set 'COMPILE_AS_C' to 'true' to compile all exercises as C sources
# this only works with Microsoft C/C++ Compiler
set (COMPILE_AS_C false)

set (FILE_NAME C27_Exercise_27.1)
set (SOURCE_CXX_LIST ${FILE_NAME}.cpp)
set (FILE_NAME2 C27_Exercise_27.2)
set (SOURCE_CXX_LIST2 ${FILE_NAME2}.cpp)


# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_CXX_LIST})
add_executable (${FILE_NAME2} ${SOURCE_CXX_LIST2})

if (${COMPILE_AS_C})
target_compile_options(${FILE_NAME} PRIVATE "/TC")
target_compile_options(${FILE_NAME2} PRIVATE "/TC")
endif()

# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Release DESTINATION Build)
