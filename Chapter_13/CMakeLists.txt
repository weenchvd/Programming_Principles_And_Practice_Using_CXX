# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_13")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)
#add_library (PPP2GUI STATIC ../GUI/GUI.cpp ../GUI/Graph.cpp ../GUI/Simple_window.cpp ../GUI/Window.cpp)

set (FILE_NAME C13_Exercise_13.1)
set (SOURCE_CXX_LIST ${FILE_NAME}.cpp)
set (FILE_NAME2 C13_Exercise_13.2)
set (SOURCE_CXX_LIST2 ${FILE_NAME2}.cpp)
#set (FILE_NAME3 C13_Exercise_13.3)
#set (SOURCE_CXX_LIST3 ${FILE_NAME3}.cpp)


# Add source to this project's executable.
add_executable (${FILE_NAME} WIN32 ${SOURCE_CXX_LIST})
target_link_libraries(${FILE_NAME} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
add_executable (${FILE_NAME2} WIN32 ${SOURCE_CXX_LIST2})
target_link_libraries(${FILE_NAME2} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)
#add_executable (${FILE_NAME3} WIN32 ${SOURCE_CXX_LIST3})
#target_link_libraries(${FILE_NAME3} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)


# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME} CONFIGURATIONS Release DESTINATION Build)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME2} CONFIGURATIONS Release DESTINATION Build)
#install (TARGETS ${FILE_NAME3} CONFIGURATIONS Debug DESTINATION Build/Debug)
#install (TARGETS ${FILE_NAME3} CONFIGURATIONS Release DESTINATION Build)
