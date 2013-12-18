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

#include "STP/Core/Tile.hpp"
#include <iostream>

namespace tmx {

Tile::Tile()
{

}

Tile::Tile(unsigned int gid, sf::IntRect tile_rect,
           const sf::Texture* texture, sf::IntRect texture_rect) :
m_gid(gid),
m_vertices(sf::Quads, 4),
m_tile_rect(tile_rect),
m_texture(texture),
m_texture_rect(texture_rect)
{
    m_vertices[0].position = sf::Vector2f(static_cast<float>(m_tile_rect.left), static_cast<float>(m_tile_rect.top));
    m_vertices[1].position = sf::Vector2f(static_cast<float>(m_tile_rect.left + m_tile_rect.width), static_cast<float>(m_tile_rect.top));
    m_vertices[2].position = sf::Vector2f(static_cast<float>(m_tile_rect.left + m_tile_rect.width), static_cast<float>(m_tile_rect.top + m_tile_rect.height));
    m_vertices[3].position = sf::Vector2f(static_cast<float>(m_tile_rect.left), static_cast<float>(m_tile_rect.top + m_tile_rect.height));

    if(texture != NULL) {
        m_vertices[0].texCoords = sf::Vector2f(static_cast<float>(texture_rect.left), static_cast<float>(texture_rect.top));
        m_vertices[1].texCoords = sf::Vector2f(static_cast<float>(texture_rect.left + texture_rect.width), static_cast<float>(texture_rect.top));
        m_vertices[2].texCoords = sf::Vector2f(static_cast<float>(texture_rect.left + texture_rect.width), static_cast<float>(texture_rect.top + texture_rect.height));
        m_vertices[3].texCoords = sf::Vector2f(static_cast<float>(texture_rect.left), static_cast<float>(texture_rect.top + texture_rect.height));
    }
};

Tile::~Tile()
{

}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_texture != NULL) {
        // apply the texture
        states.texture = m_texture;
        // draw the vertex array
        target.draw(m_vertices, states);
    }
}

}
