cmake_minimum_required(VERSION 2.8)
project( digital_binocs )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

find_package( OpenCV REQUIRED )
find_package( X11 REQUIRED )

option(BUILD_PI "description")
if(BUILD_PI)
    find_package( raspicam REQUIRED )
    add_definitions(-DBUILD_PI)
else()
    set(raspicam_LIBS "")
endif(BUILD_PI)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( include )

add_executable(binoc_control  src/binoc_control.cpp src/image_source.cpp src/image_stabalization.cpp src/display_device.cpp src/binoc_manager.cpp)
target_link_libraries( binoc_control ${OpenCV_LIBS} ${X11_LIBRARIES} ${raspicam_LIBS})


