# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_21")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)


set (FILE_NAME C21_Exercise_21.3)
set (SOURCE_CXX_LIST ${FILE_NAME}.cpp)
set (FILE_NAME2 C21_Exercise_21.4)
set (SOURCE_CXX_LIST2 ${FILE_NAME2}.cpp)
set (FILE_NAME3 C21_Exercise_21.5)
set (SOURCE_CXX_LIST3 ${FILE_NAME3}.cpp)
set (FILE_NAME4 C21_Exercise_21.6)
set (SOURCE_CXX_LIST4 ${FILE_NAME4}.cpp)
set (FILE_NAME5 C21_Exercise_21.7)
set (SOURCE_CXX_LIST5 ${FILE_NAME5}.cpp)
set (FILE_NAME6 C21_Exercise_21.8)
set (SOURCE_CXX_LIST6 ${FILE_NAME6}.cpp)
set (FILE_NAME7 C21_Exercise_21.9)
set (SOURCE_CXX_LIST7 ${FILE_NAME7}.cpp)
set (FILE_NAME8 C21_Exercise_21.10)
set (SOURCE_CXX_LIST8 ${FILE_NAME8}.cpp)


# Add source to this project's executable.
add_executable (${FILE_NAME} ${SOURCE_CXX_LIST})
add_executable (${FILE_NAME2} ${SOURCE_CXX_LIST2})
add_executable (${FILE_NAME3} ${SOURCE_CXX_LIST3})
add_executable (${FILE_NAME4} ${SOURCE_CXX_LIST4})
add_executable (${FILE_NAME5} ${SOURCE_CXX_LIST5})
add_executable (${FILE_NAME6} ${SOURCE_CXX_LIST6})
add_executable (${FILE_NAME7} ${SOURCE_CXX_LIST7})
add_executable (${FILE_NAME8} ${SOURCE_CXX_LIST8})


# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Release DESTINATION Build)
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
install (FILES C21_Exercise_21.9_Orders_001.ord CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C21_Exercise_21.9_Orders_001.ord CONFIGURATIONS Release DESTINATION Build)
install (FILES C21_Exercise_21.9_Orders_002.ord CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C21_Exercise_21.9_Orders_002.ord CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME8} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME8} CONFIGURATIONS Release DESTINATION Build)
