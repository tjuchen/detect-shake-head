cmake_minimum_required(VERSION 2.8)
project( DetectHead )
find_package( OpenCV )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( DetectHead main.cpp animation.cpp detector.cpp)
target_link_libraries( DetectHead ${OpenCV_LIBS} )
