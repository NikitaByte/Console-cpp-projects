cmake_minimum_required (VERSION 3.8)

project (Calculator CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Iclude directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Executable
add_executable(Calculator
	src/Main.cpp
	src/Calculator.cpp
)