# Se define la versión mínima del CMake
cmake_minimum_required(VERSION 2.8)

# Forza la configuración si no se ha definido (antes del comando project())
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(STP)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configuraciones limitadas" FORCE)
    mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/headers)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/STP)
