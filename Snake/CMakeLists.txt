cmake_minimum_required (VERSION 3.8)

project (Snake CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Iclude directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Executable
add_executable(Snake
	src/Main.cpp
	src/Game.cpp
)
