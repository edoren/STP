set(SRC_DIR ${PROJECT_SOURCE_DIR}/src/STP)
set(HEADER_DIR ${PROJECT_SOURCE_DIR}/include/STP)
set(EXTLIBS_DIR ${PROJECT_SOURCE_DIR}/extlibs)

set(STP_SOURCE 
    ${SRC_DIR}/Core/TileMap.cpp
    ${SRC_DIR}/Core/Parser.cpp
    ${SRC_DIR}/Core/Base64.hpp
    ${SRC_DIR}/Core/Base64.cpp
    ${SRC_DIR}/Core/Layer.cpp
    ${SRC_DIR}/Core/Tile.cpp
    ${SRC_DIR}/Core/TileSet.cpp
)

set(STP_HEADERS
    ${HEADER_DIR}/TMXLoader.hpp
    ${HEADER_DIR}/Core/TileMap.hpp
    ${HEADER_DIR}/Core/Parser.hpp
    ${HEADER_DIR}/Core/Layer.hpp
    ${HEADER_DIR}/Core/Tile.hpp
    ${HEADER_DIR}/Core/TileSet.hpp
)

set(EXT_LIBS
    ${EXTLIBS_DIR}/headers/pugixml.hpp
    ${EXTLIBS_DIR}/pugixml/pugixml.cpp
)

set(TEST
    ${PROJECT_SOURCE_DIR}/src/Test/main.cpp
)

find_package(SFML 2.1 COMPONENTS graphics window system REQUIRED)

add_library(stp SHARED ${STP_SOURCE} ${STP_HEADERS} ${EXT_LIBS})

target_link_libraries(stp ${SFML_LIBRARIES})
