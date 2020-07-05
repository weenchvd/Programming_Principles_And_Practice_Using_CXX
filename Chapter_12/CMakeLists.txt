# CMakeList.txt : CMake project for Template, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Chapter_12")

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/..)
add_library (PPP2GUI STATIC ../GUI/GUI.cpp ../GUI/Graph.cpp ../GUI/Simple_window.cpp ../GUI/Window.cpp)

set (FILE_NAME C12_Drill_12)
set (SOURCE_CXX_LIST ${FILE_NAME}.cpp)


# Add source to this project's executable.
add_executable (${FILE_NAME} WIN32 ${SOURCE_CXX_LIST})
target_link_libraries(${FILE_NAME} PPP2GUI fltk fltkforms fltkgl fltkimages fltkjpeg fltkpng fltkzlib)


# TODO: Add tests and install targets if needed.
install (TARGETS ${FILE_NAME} CONFIGURATIONS Debug DESTINATION Build/Debug)
install (TARGETS ${FILE_NAME} CONFIGURATIONS Release DESTINATION Build)
install (FILES C12_Drill_12_Fry.jpg C12_Drill_12_snow_cpp.gif CONFIGURATIONS Debug DESTINATION Build/Debug)
install (FILES C12_Drill_12_Fry.jpg C12_Drill_12_snow_cpp.gif CONFIGURATIONS Release DESTINATION Build)
