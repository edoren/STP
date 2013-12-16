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

#include "STP/Core/Layer.hpp"

namespace tmx {

Layer::Layer(const std::string& name, unsigned int width, unsigned int height, float opacity, bool visible) :
m_name(name),
m_width(width),
m_height(height),
m_opacity(opacity),
visible(visible)
{
    // Reserve space for each vector to avoid reallocate
    m_tiles.reserve(m_height);
    for (int i = 0; i < m_height; i++) {
        std::vector<tmx::Tile> newvec;
        newvec.reserve(m_width);
        m_tiles.push_back(newvec);
    }
};

Layer::~Layer()
{

}

int Layer::addTile(tmx::Tile newtile) {
    for (int i = 0; i < m_height; i++) {  
        if(m_tiles[i].size() < m_width) {
            m_tiles[i].push_back(newtile);
            return 0;
        }
    }
    return -1;
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int y = 0; y < m_tiles.size(); y++) {
        for (int x = 0; x < m_tiles[y].size(); x++) {
            target.draw(m_tiles[y][x]);
        }
    }
}

}
