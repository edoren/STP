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

#include "STP/Core/TileMap.hpp"

namespace tmx {

TileMap::TileMap(float version, const std::string& orientation, unsigned int width,
                 unsigned int height, unsigned int tilewidth, unsigned int tileheight) :
m_version    (version),
m_orientation(orientation),
m_width      (width),
m_height     (height),
m_tilewidth  (tilewidth),
m_tileheight (tileheight)
{
    
}

TileMap::~TileMap()
{

}

void TileMap::addLayer(tmx::Layer newlayer) {
    m_layers.push_back(newlayer);
}

void TileMap::addTileSet(tmx::TileSet newtileset) {
    m_tilesets.push_back(newtileset);
}

tmx::TileSet* TileMap::getTileSet(unsigned int gid) {
    if(gid == 0) return NULL;
    for (unsigned int i = 0; i < m_tilesets.size(); ++i) {
        if(gid >= m_tilesets[i].getFirstGID() && gid <= m_tilesets[i].getLastGID())
            return &m_tilesets[i];
    }
    return NULL;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (unsigned int i = 0; i < m_layers.size(); i++) {
        if(m_layers[i].visible == true)
            target.draw(m_layers[i]);
    }
}

}
