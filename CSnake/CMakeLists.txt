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

# Link libraries (if needed)
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(GLIB REQUIRED glib-2.0)
# target_link_libraries(${PROJECT_NAME} ${GLIB_LIBRARIES})
# target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS})

# Platform-specific linking
#if(WIN32)
#    # Windows-specific libraries
#    # target_link_libraries(${PROJECT_NAME} ws2_32)
#elseif(UNIX AND NOT APPLE)
#    # Linux-specific libraries
#    target_link_libraries(${PROJECT_NAME} m) # Math library
#    # target_link_libraries(${PROJECT_NAME} pthread) # Threading
#elseif(APPLE)
#    # macOS-specific libraries
#    target_link_libraries(${PROJECT_NAME} m)
#endif()

# Custom target for cleaning
add_custom_target(clean-all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMENT "Cleaning all generated files"
)

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# Optional: Install headers for library projects
# install(FILES ${HEADERS}
#     DESTINATION include/${PROJECT_NAME}
# )

# Optional: Create a library instead of executable
# add_library(${PROJECT_NAME}_lib STATIC ${SOURCES})
# target_include_directories(${PROJECT_NAME}_lib PUBLIC include)

# Optional: Testing support
# enable_testing()
# add_subdirectory(tests)

# Print build information
    #message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
    #message(STATUS "C Compiler: ${CMAKE_C_COMPILER_ID}")
    #message(STATUS "C Standard: ${CMAKE_C_STANDARD}")

# Optional: CPack for packaging
include(CPack)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A sample C project")
set(CPACK_GENERATOR "TGZ;ZIP")

# Optional: Find and use external libraries
# Example for finding and using a common library:
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(LIBCURL REQUIRED libcurl)
# if(LIBCURL_FOUND)
#     target_link_libraries(${PROJECT_NAME} ${LIBCURL_LIBRARIES})
#     target_include_directories(${PROJECT_NAME} PRIVATE ${LIBCURL_INCLUDE_DIRS})
#     target_compile_options(${PROJECT_NAME} PRIVATE ${LIBCURL_CFLAGS_OTHER})
# endif()