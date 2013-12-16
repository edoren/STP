////////////////////////////////////////////////////////////
//
// The MIT License (MIT)
//
// STP - SFML TMX Parser
// Copyright (c) 2013 Manuel Sabogal
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////////

#ifndef STP_PARSER_HPP
#define STP_PARSER_HPP

#include "STP/Core/TileMap.hpp"
#include "pugixml.hpp"
#include <sstream>
#include <vector>

namespace tmx {

class Parser {
public:
    Parser();
    ~Parser();

    tmx::TileMap parseFile(const std::string &file_to_parse);

private:
    unsigned int m_width, m_height, m_tilewidth, m_tileheight;
    tmx::TileMap* m_tilemap;
    std::string m_working_dir;

    int parseMap();
    tmx::TileSet parseTileSet(const pugi::xml_node& tileset_node);
    tmx::Layer parseLayer(const pugi::xml_node& layer_node);
    void addTile(tmx::Layer& layer, int gid, sf::IntRect tile_rect);
    int parseObjectGroup();
    int parseImageLayer();
};

}

#endif // STP_PARSER_HPP
