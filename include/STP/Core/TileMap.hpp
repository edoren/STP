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

#ifndef STP_TILEMAP_HPP
#define STP_TILEMAP_HPP

#include "STP/Core/TileSet.hpp"
#include "STP/Core/Layer.hpp"
#include <vector>

namespace tmx {

class TileMap : public sf::Drawable {
public:
    TileMap(float _version, const std::string& _orientation, unsigned int _width, unsigned int _height, unsigned int _tilewidth, unsigned int _tileheight);
    ~TileMap();

    void addLayer(tmx::Layer newlayer);
    void addTileSet(tmx::TileSet newtileset);

    // Return the tileset attached to the global id
    tmx::TileSet* getTileSet(unsigned int gid);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<tmx::Layer> m_layers;
private:
    float m_version;
    std::string m_orientation;
    unsigned int m_width, m_height, m_tilewidth, m_tileheight;

    std::vector<tmx::TileSet> m_tilesets;
};

}

#endif // STP_TILEMAP_HPP
