CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(osfile_prac)

SET(osfile_prac_C_FLAGS)
SET(osfile_prac_CXX_FLAGS)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${osfile_prac_SOURCE_DIR}/build)

ADD_DEFINITIONS(-DUNIX)
MESSAGE(STATUS "Compiling on Linux")

SET(osfile_prac_CXX_FLAGS "${osfile_prac_CXX_FLAGS} -Wall -W -lpthread -std=c++11 -g")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${osfile_prac_CXX_FLAGS}")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${osfile_prac_C_FLAGS}")

INCLUDE_DIRECTORIES(${osfile_prac_SOURCE_DIR})
ADD_EXECUTABLE(osfile_prac osfile.cc)

