﻿# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_26")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)


set (FILE_NAME C26_BinarySearch_01)
set (SOURCE_CXX_LIST ${FILE_NAME}.cpp)
set (FILE_NAME2 C26_Exercise_26.1)
set (SOURCE_CXX_LIST2 ${FILE_NAME2}.cpp)
set (FILE_NAME3 C26_Exercise_26.2)
set (SOURCE_CXX_LIST3 ${FILE_NAME3}.cpp)
set (FILE_NAME4 C26_Exercise_26.3)
set (SOURCE_CXX_LIST4 ${FILE_NAME4}.cpp)
set (FILE_NAME5 C26_Exercise_26.4)
set (SOURCE_CXX_LIST5 ${FILE_NAME5}.cpp)
set (FILE_NAME6 C26_Exercise_26.5)
set (SOURCE_CXX_LIST6 ${FILE_NAME6}.cpp)
set (FILE_NAME7 C26_Exercise_26.6)
set (SOURCE_CXX_LIST7 ${FILE_NAME7}.cpp)
set (FILE_NAME9 C26_Exercise_26.8)
set (SOURCE_CXX_LIST9 ${FILE_NAME9}.cpp)
set (FILE_NAME10 C26_Exercise_26.9)
set (SOURCE_CXX_LIST10 ${FILE_NAME10}.cpp)
set (FILE_NAME12 C26_Exercise_26.11)
set (SOURCE_CXX_LIST12 ${FILE_NAME12}.cpp)
set (FILE_NAME13 C26_Exercise_26.12)
set (SOURCE_CXX_LIST13 ${FILE_NAME13}.cpp)
set (FILE_NAME14 C26_Exercise_26.13)
set (SOURCE_CXX_LIST14 ${FILE_NAME14}.cpp)
set (FILE_NAME15 C26_Exercise_26.14)
set (SOURCE_CXX_LIST15 ${FILE_NAME15}.cpp)


# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_CXX_LIST})
add_executable (${FILE_NAME2} ${SOURCE_CXX_LIST2})
add_executable (${FILE_NAME3} ${SOURCE_CXX_LIST3})
add_executable (${FILE_NAME4} ${SOURCE_CXX_LIST4})
add_executable (${FILE_NAME5} ${SOURCE_CXX_LIST5})
add_executable (${FILE_NAME6} ${SOURCE_CXX_LIST6})
add_executable (${FILE_NAME7} ${SOURCE_CXX_LIST7})
add_executable (${FILE_NAME9} ${SOURCE_CXX_LIST9})
target_link_libraries(${FILE_NAME9} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME10} ${SOURCE_CXX_LIST10})
target_link_libraries(${FILE_NAME10} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME12} ${SOURCE_CXX_LIST12})
add_executable (${FILE_NAME13} ${SOURCE_CXX_LIST13})
add_executable (${FILE_NAME14} ${SOURCE_CXX_LIST14})
add_executable (${FILE_NAME15} ${SOURCE_CXX_LIST15})


# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME3} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME3} CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.2_test_int.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.2_test_int.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.2_test_double.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.2_test_double.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.2_test_string.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.2_test_string.txt CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME4} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME4} CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.3_test_int.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.3_test_int.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.3_test_int_g.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.3_test_int_g.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.3_test_double.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.3_test_double.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.3_test_double_g.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.3_test_double_g.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.3_test_string.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.3_test_string.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.3_test_string_g.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.3_test_string_g.txt CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME5} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME5} CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.4_test_int.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.4_test_int.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.4_test_double.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.4_test_double.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.4_test_string.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.4_test_string.txt CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME6} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME6} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME7} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME7} CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.6_input.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.6_input.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.6_solution.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.6_solution.txt CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME9} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME9} CONFIGURATIONS Release DESTINATION Build)
install (FILES C26_Exercise_26.8_house.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C26_Exercise_26.8_house.txt CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME10} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME10} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME12} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME12} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME13} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME13} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME14} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME14} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME15} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME15} CONFIGURATIONS Release DESTINATION Build)
