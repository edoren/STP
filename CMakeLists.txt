cmake_minimum_required(VERSION 2.8)

macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
mark_as_advanced(CMAKE_CONFIGURATION_TYPES)

# Project name
project(STP)

# Predefined configuration options
set_option(STP_SHARED_LIBS TRUE BOOL "Build shared libraries (use shared SFML librares)")
set_option(STP_BUILD_EXAMPLES FALSE BOOL "Build example projects")
set_option(STP_BUILD_DOC FALSE BOOL "Create HTML documentation (requires Doxygen)")

# Tell CMake where to find the FindSFML.cmake
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

# Include the config file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

# If compiler is GNU GCC based it enable the warnings
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions("-Wall")
endif()

# Adding C++11 support in GCC compiler and Clang compiler
if(${COMPILER} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++0x -stdlib=libc++")
elseif(${COMPILER} STREQUAL "GCC")
    set(CMAKE_CXX_FLAGS "-std=c++0x")
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

if(STP_BUILD_DOC)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/doc)
endif()

# Source directory
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/STP)

# Install the headers
install(DIRECTORY include DESTINATION . COMPONENT devel)
