cmake_minimum_required(VERSION 2.8)
project( digital_binocs )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( include )

add_executable(binoc_control  src/binoc_control.cpp src/image_source.cpp)
target_link_libraries( binoc_control ${OpenCV_LIBS} )

