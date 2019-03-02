
cmake_minimum_required(VERSION 3.0)

project( myslic )

find_package( OpenCV REQUIRED )

add_executable( myslic slic_test.cc slic.h slic.cc )

target_link_libraries( myslic ${OpenCV_LIBS} )
