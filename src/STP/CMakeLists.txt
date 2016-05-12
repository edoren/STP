set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

set(STP_SOURCE
    "${SRC_DIR}/STP/Core/Properties.cpp"
    "${SRC_DIR}/STP/Core/MapObject.cpp"
    "${SRC_DIR}/STP/Core/Parser.cpp"
    "${SRC_DIR}/STP/Core/Base64.cpp"
    "${SRC_DIR}/STP/Core/Layer.cpp"
    "${SRC_DIR}/STP/Core/ObjectGroup.cpp"
    "${SRC_DIR}/STP/Core/Image.cpp"
    "${SRC_DIR}/STP/Core/ImageLayer.cpp"
    "${SRC_DIR}/STP/Core/TileMap.cpp"
    "${SRC_DIR}/STP/Core/TileSet.cpp"
)

set(STP_HEADERS
    "${SRC_DIR}/STP/Core/Parser.hpp"
    "${SRC_DIR}/STP/Core/Base64.hpp"
    "${INCLUDE_DIR}/STP/Config.hpp"
    "${INCLUDE_DIR}/STP/Core/Properties.hpp"
    "${INCLUDE_DIR}/STP/Core/MapObject.hpp"
    "${INCLUDE_DIR}/STP/Core/Layer.hpp"
    "${INCLUDE_DIR}/STP/Core/ObjectGroup.hpp"
    "${INCLUDE_DIR}/STP/Core/Image.hpp"
    "${INCLUDE_DIR}/STP/Core/ImageLayer.hpp"
    "${INCLUDE_DIR}/STP/Core/TileSet.hpp"
    "${INCLUDE_DIR}/STP/Core/TileMap.hpp"
    "${INCLUDE_DIR}/STP/TMXLoader.hpp"
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

# Install the library
install(TARGETS ${STP_LIB} RUNTIME DESTINATION bin COMPONENT bin
                           LIBRARY DESTINATION lib COMPONENT bin
                           ARCHIVE DESTINATION lib COMPONENT bin)

# Install the headers
install(DIRECTORY ${INCLUDE_DIR} DESTINATION . COMPONENT devel)
