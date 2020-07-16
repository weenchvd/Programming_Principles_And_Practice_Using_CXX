# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_13")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)


set (FILE_NAME C13_Exercise_13.1)
set (SOURCE_CXX_LIST ${FILE_NAME}.cpp)
set (FILE_NAME2 C13_Exercise_13.2)
set (SOURCE_CXX_LIST2 ${FILE_NAME2}.cpp)
set (FILE_NAME3 C13_Exercise_13.3)
set (SOURCE_CXX_LIST3 ${FILE_NAME3}.cpp)
set (FILE_NAME4 C13_Exercise_13.4)
set (SOURCE_CXX_LIST4 ${FILE_NAME4}.cpp)
set (FILE_NAME5 C13_Exercise_13.5)
set (SOURCE_CXX_LIST5 ${FILE_NAME5}.cpp)
set (FILE_NAME6 C13_Exercise_13.6)
set (SOURCE_CXX_LIST6 ${FILE_NAME6}.cpp)
set (FILE_NAME7 C13_Exercise_13.7)
set (SOURCE_CXX_LIST7 ${FILE_NAME7}.cpp)


# Add source to this project's executable.
add_executable (${FILE_NAME} WIN32 ${SOURCE_CXX_LIST})
target_link_libraries(${FILE_NAME} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME2} WIN32 ${SOURCE_CXX_LIST2})
target_link_libraries(${FILE_NAME2} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME3} WIN32 ${SOURCE_CXX_LIST3})
target_link_libraries(${FILE_NAME3} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME4} WIN32 ${SOURCE_CXX_LIST4})
target_link_libraries(${FILE_NAME4} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME5} WIN32 ${SOURCE_CXX_LIST5})
target_link_libraries(${FILE_NAME5} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME6} WIN32 ${SOURCE_CXX_LIST6})
target_link_libraries(${FILE_NAME6} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME7} WIN32 ${SOURCE_CXX_LIST7})
target_link_libraries(${FILE_NAME7} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)


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
