﻿# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_24")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)


set (FILE_NAME C24_Exercise_24.1)
set (SOURCE_CXX_LIST ${FILE_NAME}.cpp)
set (FILE_NAME2 C24_Exercise_24.2)
set (SOURCE_CXX_LIST2 ${FILE_NAME2}.cpp)
#set (FILE_NAME3 C24_Exercise_24.3)
#set (SOURCE_CXX_LIST3 ${FILE_NAME3}.cpp)
set (FILE_NAME4 C24_Exercise_24.4)
set (SOURCE_CXX_LIST4 ${FILE_NAME4}.cpp)
set (FILE_NAME5 C24_Exercise_24.5)
set (SOURCE_CXX_LIST5 ${FILE_NAME5}.cpp)
set (FILE_NAME6 C24_Exercise_24.6)
set (SOURCE_CXX_LIST6 ${FILE_NAME6}.cpp)
set (FILE_NAME7 C24_Exercise_24.7)
set (SOURCE_CXX_LIST7 ${FILE_NAME7}.cpp)
set (FILE_NAME8 C24_Exercise_24.8)
set (SOURCE_CXX_LIST8 ${FILE_NAME8}.cpp)
set (FILE_NAME9 C24_Exercise_24.9)
set (SOURCE_CXX_LIST9 ${FILE_NAME9}.cpp)
set (FILE_NAME10 C24_Exercise_24.10)
set (SOURCE_CXX_LIST10 ${FILE_NAME10}.cpp)
set (FILE_NAME11 C24_Exercise_24.11)
set (SOURCE_CXX_LIST11 ${FILE_NAME11}.cpp)
set (FILE_NAME12 C24_Exercise_24.12)
set (SOURCE_CXX_LIST12 ${FILE_NAME12}.cpp)


# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_CXX_LIST})
add_executable (${FILE_NAME2} ${SOURCE_CXX_LIST2})
#add_executable (${FILE_NAME3} ${SOURCE_CXX_LIST3})
add_executable (${FILE_NAME4} ${SOURCE_CXX_LIST4})
add_executable (${FILE_NAME5} ${SOURCE_CXX_LIST5})
add_executable (${FILE_NAME6} ${SOURCE_CXX_LIST6})
add_executable (${FILE_NAME7} ${SOURCE_CXX_LIST7})
add_executable (${FILE_NAME8} ${SOURCE_CXX_LIST8})
add_executable (${FILE_NAME9} ${SOURCE_CXX_LIST9})
add_executable (${FILE_NAME10} ${SOURCE_CXX_LIST10})
add_executable (${FILE_NAME11} ${SOURCE_CXX_LIST11})
add_executable (${FILE_NAME12} ${SOURCE_CXX_LIST12})


# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Release DESTINATION Build)
#install (TARGETS ${FILE_NAME3} CONFIGURATIONS Debug DESTINATION Build/Debug)
#install (TARGETS ${FILE_NAME3} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME4} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME4} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME5} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME5} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME6} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME6} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME7} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME7} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME8} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME8} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME9} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME9} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME10} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME10} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME11} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME11} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME12} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME12} CONFIGURATIONS Release DESTINATION Build)
