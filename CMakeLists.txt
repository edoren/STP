cmake_minimum_required(VERSION 2.8)

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
    mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

# Project name
project(STP)

# Version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

# Predefined configuration options
set(STP_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries (use shared SFML librares)")
set(STP_BUILD_EXAMPLES FALSE CACHE BOOL "Build example projects")
set(STP_BUILD_DOC FALSE CACHE BOOL "Create HTML documentation (requires Doxygen)")

# Tell CMake where to find the FindSFML.cmake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

# If compiler is GNU GCC based it enable the warnings
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions ("-Wall")
endif()

# Adding C++11 support in GCC compiler and Clang compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_definitions("-std=c++0x -stdlib=libc++")
elseif(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions("-std=c++0x")
endif()

# Set the SFML_ROOT folder
set(SFML_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/SFML)

# Preprocessor definitions and include directories
add_definitions(-DSTP_EXPORTS)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers)
if(NOT STP_SHARED_LIBS)
    add_definitions(-DSTP_STATIC)
endif()

# Enable the folders in the projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# Source directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/STP)
