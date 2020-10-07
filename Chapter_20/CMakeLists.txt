# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_20")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)


set (FILE_NAME C20_Drill_20)
set (SOURCE_CXX_LIST ${FILE_NAME}.cpp)
set (FILE_NAME2 C20_Exercise_20.2)
set (SOURCE_CXX_LIST2 ${FILE_NAME2}.cpp)
set (FILE_NAME3 C20_Exercise_20.3)
set (SOURCE_CXX_LIST3 ${FILE_NAME3}.cpp)
set (FILE_NAME4 C20_Exercise_20.4)
set (SOURCE_CXX_LIST4 ${FILE_NAME4}.cpp)
set (FILE_NAME5 C20_Exercise_20.5)
set (SOURCE_CXX_LIST5 ${FILE_NAME5}.cpp)
set (FILE_NAME6 C20_Exercise_20.6)
set (SOURCE_CXX_LIST6 ${FILE_NAME6}.cpp)
set (FILE_NAME7 C20_Exercise_20.7)
set (SOURCE_CXX_LIST7 ${FILE_NAME7}.cpp)
set (FILE_NAME8 C20_Exercise_20.8)
set (SOURCE_CXX_LIST8 ${FILE_NAME8}.cpp)
set (FILE_NAME9 C20_Exercise_20.9)
set (SOURCE_CXX_LIST9 ${FILE_NAME9}.cpp)


# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_CXX_LIST})
add_executable (${FILE_NAME2} ${SOURCE_CXX_LIST2})
add_executable (${FILE_NAME3} ${SOURCE_CXX_LIST3})
add_executable (${FILE_NAME4} ${SOURCE_CXX_LIST4})
add_executable (${FILE_NAME5} ${SOURCE_CXX_LIST5})
add_executable (${FILE_NAME6} ${SOURCE_CXX_LIST6})
add_executable (${FILE_NAME7} ${SOURCE_CXX_LIST7})
add_executable (${FILE_NAME8} ${SOURCE_CXX_LIST8})
add_executable (${FILE_NAME9} ${SOURCE_CXX_LIST9})


# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Release DESTINATION Build)
install (FILES C20_Exercise_20.2_Jack.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C20_Exercise_20.2_Jack.txt CONFIGURATIONS Release DESTINATION Build)
install (FILES C20_Exercise_20.2_Jill.txt CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C20_Exercise_20.2_Jill.txt CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME3} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME3} CONFIGURATIONS Release DESTINATION Build)
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
