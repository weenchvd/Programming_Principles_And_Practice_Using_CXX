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


# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_CXX_LIST})
add_executable (${FILE_NAME2} ${SOURCE_CXX_LIST2})
add_executable (${FILE_NAME3} ${SOURCE_CXX_LIST3})
add_executable (${FILE_NAME4} ${SOURCE_CXX_LIST4})


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
