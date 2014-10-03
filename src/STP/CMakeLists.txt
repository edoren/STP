set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/STP)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include/STP)

set(EXTLIBS_DIR ${PROJECT_SOURCE_DIR}/extlibs)

set(STP_SOURCE
    ${SRC_DIR}/Core/Properties.cpp
    ${SRC_DIR}/Core/MapObject.cpp
    ${SRC_DIR}/Core/Parser.cpp
    ${SRC_DIR}/Core/Base64.cpp
    ${SRC_DIR}/Core/Layer.cpp
    ${SRC_DIR}/Core/ObjectGroup.cpp
    ${SRC_DIR}/Core/Image.cpp
    ${SRC_DIR}/Core/ImageLayer.cpp
    ${SRC_DIR}/Core/TileMap.cpp
    ${SRC_DIR}/Core/TileSet.cpp
)

set(STP_HEADERS
    ${SRC_DIR}/Core/Parser.hpp
    ${SRC_DIR}/Core/Base64.hpp
    ${HEADER_DIR}/Config.hpp
    ${HEADER_DIR}/Core/Properties.hpp
    ${HEADER_DIR}/Core/MapObject.hpp
    ${HEADER_DIR}/Core/Layer.hpp
    ${HEADER_DIR}/Core/ObjectGroup.hpp
    ${HEADER_DIR}/Core/Image.hpp
    ${HEADER_DIR}/Core/ImageLayer.hpp
    ${HEADER_DIR}/Core/TileSet.hpp
    ${HEADER_DIR}/Core/TileMap.hpp
    ${HEADER_DIR}/TMXLoader.hpp

)

set(PUGIXML_SOURCE
    ${EXTLIBS_DIR}/pugixml/pugixml.cpp
    ${EXTLIBS_DIR}/headers/pugixml.hpp
    ${EXTLIBS_DIR}/headers/pugiconfig.hpp
)

# Library name
set(STP_LIB ${PROJECT_NAME})

# Set the output path for the library and runtime libraries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")

# Build the library
if(STP_SHARED_LIBS)
    add_library(${STP_LIB} SHARED ${STP_SOURCE} ${STP_HEADERS})
    set_target_properties(${STP_LIB} PROPERTIES DEBUG_POSTFIX -d)
    if (${OS} STREQUAL "Windows" AND ${COMPILER} STREQUAL "MinGW")
        # on Windows/gcc get rid of "lib" prefix for shared libraries,
        # and transform the ".dll.a" suffix into ".a" for import libraries
        set_target_properties(${STP_LIB} PROPERTIES PREFIX "")
        set_target_properties(${STP_LIB} PROPERTIES IMPORT_SUFFIX ".a")
    endif()
else()
    add_library(${STP_LIB} STATIC ${STP_SOURCE} ${STP_HEADERS})
    set_target_properties(${STP_LIB} PROPERTIES DEBUG_POSTFIX -s-d)
    set_target_properties(${STP_LIB} PROPERTIES RELEASE_POSTFIX -s)
endif()

# Configuration for Visual Studio
if(${OS} STREQUAL "Windows" AND ${COMPILER} STREQUAL "MSVC")
    # Add the include directories for external libraries for search
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} ${EXTLIBS_DIR}/headers)
    set(CMAKE_LIBRARY_PATH ${CMAKE_INCLUDE_PATH} ${EXTLIBS_DIR}/libs-win32)

    # Add the libraries of the external libraries for search
    if(${COMPILER} STREQUAL "MSVC")
        # Improve the visual studio project generator
        source_group("Source Files\\Core" FILES ${STP_SOURCE})
        source_group("Header Files\\Core" FILES ${STP_HEADERS})
        if(${COMPILER_ARCH} EQUAL 32)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${PROJECT_SOURCE_DIR}/extlibs/lib-msvc/x86)
        elseif(${COMPILER_ARCH} EQUAL 64)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${PROJECT_SOURCE_DIR}/extlibs/lib-msvc/x64)
        endif()
    endif()
endif()

# Find PugiXML
find_package(PugiXML)
if(PUGIXML_FOUND)
    include_directories(${PUGIXML_INCLUDE_DIR})
    target_link_libraries(${STP_LIB} ${PUGIXML_LIBRARY})
else()
    message("-> Building PugiXML from source.")
    if(${OS} STREQUAL "Windows")
        add_library(pugixml STATIC ${PUGIXML_SOURCE})
    else()
        add_library(pugixml SHARED ${PUGIXML_SOURCE})
    endif()
    target_link_libraries(${STP_LIB} pugixml)
    install(TARGETS pugixml RUNTIME DESTINATION bin COMPONENT bin
                            LIBRARY DESTINATION lib COMPONENT bin
                            ARCHIVE DESTINATION lib COMPONENT bin)
endif()

# Find Zlib
find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(${STP_LIB} ${ZLIB_LIBRARIES})
endif()

# Find SFML
if(NOT SFML_FOUND)
    find_package(SFML 2 COMPONENTS graphics window system)
endif()
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${STP_LIB} ${SFML_LIBRARIES})
else()
    message("\n-> SFML directory not found. Put the SFML's top-level path (containing \"include\" and \"lib\" directories) in the /extlibs folder.\n")
endif()

# Install rules
install(TARGETS ${STP_LIB} RUNTIME DESTINATION bin COMPONENT bin
                           LIBRARY DESTINATION lib COMPONENT bin
                           ARCHIVE DESTINATION lib COMPONENT bin)
