#ifndef STP_PARSER_HPP
#define STP_PARSER_HPP

#include "STP/Core/TileMap.hpp"
#include "pugixml.hpp"
#include <sstream>
#include <vector>

namespace TMX {

class Parser {
public:
    Parser();
    ~Parser();

    TMX::TileMap parseFile(const std::string &file_to_parse);

private:
    unsigned int m_width, m_height, m_tilewidth, m_tileheight;
    TMX::TileMap* m_tilemap;
    std::string m_working_dir;

    int parseMap();
    TMX::TileSet parseTileSet(const pugi::xml_node& tileset_node);
    TMX::Layer parseLayer(const pugi::xml_node& layer_node);
    void addTile(TMX::Layer& layer, int gid, sf::IntRect tile_rect);
    int parseObjectGroup();
    int parseImageLayer();
};

}

#endif // STP_PARSER_HPP
