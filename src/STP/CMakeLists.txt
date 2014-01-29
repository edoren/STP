set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/STP)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include/STP)

set(EXTLIBS_DIR ${PROJECT_SOURCE_DIR}/extlibs)

set(STP_SOURCE 
    ${SRC_DIR}/Core/Properties.cpp
    ${SRC_DIR}/Core/MapObject.cpp
    ${SRC_DIR}/Core/Parser.hpp
    ${SRC_DIR}/Core/Parser.cpp
    ${SRC_DIR}/Core/Base64.hpp
    ${SRC_DIR}/Core/Base64.cpp
    ${SRC_DIR}/Core/Layer.cpp
    ${SRC_DIR}/Core/Object.cpp
    ${SRC_DIR}/Core/ObjectGroup.cpp
    ${SRC_DIR}/Core/Image.cpp
    ${SRC_DIR}/Core/ImageLayer.cpp
    ${SRC_DIR}/Core/TileMap.cpp
    ${SRC_DIR}/Core/TileSet.cpp
)

set(STP_HEADERS
    ${HEADER_DIR}/Config.hpp
    ${HEADER_DIR}/Core/Properties.hpp
    ${HEADER_DIR}/Core/MapObject.hpp
    ${HEADER_DIR}/Core/Layer.hpp
    ${HEADER_DIR}/Core/Object.hpp
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

# Set the output path for the 
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# Build the library
if(STP_SHARED_LIBS)
    add_library(${STP_LIB} SHARED ${STP_SOURCE} ${STP_HEADERS} ${PUGIXML_SOURCE})
    set_target_properties(${STP_LIB} PROPERTIES DEBUG_POSTFIX -d)
    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set_target_properties(${STP_LIB} PROPERTIES SUFFIX "-${VERSION_MAJOR}${CMAKE_SHARED_LIBRARY_SUFFIX}")
    endif()
    if (${CMAKE_SYSTEM_NAME} MATCHES "Windows" AND CMAKE_COMPILER_IS_GNUCXX)
        # on Windows/gcc get rid of "lib" prefix for shared libraries,
        # and transform the ".dll.a" suffix into ".a" for import libraries
        set_target_properties(${STP_LIB} PROPERTIES PREFIX "")
        set_target_properties(${STP_LIB} PROPERTIES IMPORT_SUFFIX ".a")
    endif()
else()
    add_library(${STP_LIB} STATIC ${STP_SOURCE} ${STP_HEADERS} ${PUGIXML_SOURCE})
    set_target_properties(${STP_LIB} PROPERTIES DEBUG_POSTFIX -s-d)
    set_target_properties(${STP_LIB} PROPERTIES RELEASE_POSTFIX -s)
endif()

# Configuration for some IDEs
set_target_properties(${STP_LIB} PROPERTIES FOLDER "GDE")

# Find SFML
find_package(SFML 2.1 COMPONENTS graphics window system REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${STP_LIB} ${SFML_LIBRARIES})
else()
    message("\n-> SFML directory not found. Put the SFML's top-level path (containing \"include\" and \"lib\" directories) in the /extlibs folder.\n")
endif()
