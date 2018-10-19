
# Set a minimum version of CMake to be used, depending on the syntax of the CMakeLists files
cmake_minimum_required(VERSION 3.0)

# Give the project a cutsie name
project(hello)

aux_source_directory(. DIR_SRCS)
add_subdirectory(libs)

# Tell the compiler to search these directories for include files
# include_directories()

#Finally create the executable that we want
add_executable(hello ${DIR_SRCS})

# Link it against the required libraries
target_link_libraries(hello searchtest)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0x)
if (COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0x)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no c++11 support. Please use a different c++ compiler")
endif()
