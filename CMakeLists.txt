###############################################################################
# CMake configuration

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

###############################################################################
# Project configuration

# Project name
project(STP)

# Predefined configuration options
set_option(STP_SHARED_LIBS TRUE BOOL "Build shared libraries (use shared SFML libraries)")
set_option(STP_BUILD_TESTS FALSE BOOL "Build test projects")
set_option(STP_BUILD_DOC FALSE BOOL "Create HTML documentation (requires Doxygen)")

# Enable the folders in the projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

# Tell CMake where to find additional modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

# Include the config file
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake")

# Preprocessor definitions and include directories
add_definitions(-DSTP_EXPORTS)
if(NOT STP_SHARED_LIBS)
    add_definitions(-DSTP_STATIC)
endif()

###############################################################################
# Compiler configuration

# Adding C++11 support in GCC compiler and Clang compiler
if(${COMPILER} STREQUAL "Clang")
    if(${OS} STREQUAL "Linux")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libstdc++")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
    endif()
elseif(${COMPILER} STREQUAL "GCC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

# If compiler is GNU GCC or Clang enable the warnings
if(${COMPILER} STREQUAL "GCC" OR ${COMPILER} STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

###############################################################################
# Third party libraries configuration

set(DEFAULT_OPTION TRUE)
if(${OS} STREQUAL "Windows")
    set(DEFAULT_OPTION FALSE)
endif()

set_option(USE_SHARED_PUGIXML ${DEFAULT_OPTION} BOOL "Use your installed copy of PugiXML")
set_option(USE_SHARED_ZLIB ${DEFAULT_OPTION} BOOL "Use your installed copy of zlib")

###############################################################################
# Directories

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_PROFILE "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

set(DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extlibs")
set(TEMP_DIR "${CMAKE_BINARY_DIR}/obj")

###############################################################################
# Build the dependencies

add_subdirectory(${DEPENDENCIES_DIR})
include_directories(${DEPENDENCIES_INCLUDES})

###############################################################################
# Build STP

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/STP")

###############################################################################
# Build the documentation

if(STP_BUILD_DOC)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/doc")
endif()

###############################################################################
# Build the tests

if(STP_BUILD_TESTS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/tests")
endif()

###############################################################################
