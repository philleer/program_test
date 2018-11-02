cmake_minimum_required(VERSION 3.0)
project( disimg )
find_package( OpenCV REQUIRED )
add_executable( disimg disimg.cc )
target_link_libraries( disimg ${OpenCV_LIBS} )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
message( STATUS "optional: -std=c++11")
