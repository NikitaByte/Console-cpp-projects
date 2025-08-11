# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Project name and version
project(CSnake VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific options
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    # GCC and Clang options
    set(CMAKE_C_FLAGS "-Wall -Wextra")
    set(CMAKE_C_FLAGS_DEBUG "-g -O0 -DDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
elseif(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    # MSVC options
    set(CMAKE_C_FLAGS "/W4")
    set(CMAKE_C_FLAGS_DEBUG "/Zi /Od /DDEBUG")
    set(CMAKE_C_FLAGS_RELEASE "/O2 /DNDEBUG")
endif()

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.c
    src/game.c
    src/deque.c
    src/conhdl.c
    src/vector2.c
)

# Header files (for IDE support)
set(HEADERS
    include/vector2.h
    include/conhdl.h
    include/deque.h
    include/game.h
    # Add more header files here
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)