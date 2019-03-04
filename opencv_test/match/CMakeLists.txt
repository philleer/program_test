
cmake_minimum_required( VERSION 3.0 )

project( match )

find_package( OpenCV REQUIRED )

add_executable( match match.cc )

target_link_libraries( match ${OpenCV_LIBS} )
