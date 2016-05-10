set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/STP)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include/STP)

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

# Library name
set(STP_LIB ${PROJECT_NAME})

# Build the library
if(STP_SHARED_LIBS)
    add_library(${STP_LIB} SHARED ${STP_SOURCE} ${STP_HEADERS})
    set_target_properties(${STP_LIB} PROPERTIES DEBUG_POSTFIX -d)
    if (${OS} STREQUAL "Windows" AND ${COMPILER} STREQUAL "GCC")
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

target_link_libraries(${STP_LIB}
    ${SFML_LIBRARIES}
    ${PUGIXML_LIBRARIES}
    ${ZLIB_LIBRARIES}
)

# Install rules
install(TARGETS ${STP_LIB} RUNTIME DESTINATION bin COMPONENT bin
                           LIBRARY DESTINATION lib COMPONENT bin
                           ARCHIVE DESTINATION lib COMPONENT bin)
