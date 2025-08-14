cmake_minimum_required (VERSION 3.8)

project (Stdlib CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Iclude directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Executable
add_executable (Stdlib
	src/Main.cpp
 "include/Vector2.h")
