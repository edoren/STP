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

#ifndef STP_TILE_HPP
#define STP_TILE_HPP

#include "STP/Config.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"

namespace tmx {

class STP_API Tile : public sf::Drawable {
public:
    Tile();
    Tile(unsigned int gid, sf::IntRect tile_rect, 
         const sf::Texture* texture, sf::IntRect texture_rect = sf::IntRect(0,0,0,0));
    ~Tile();

private:
    unsigned int m_gid;

    sf::IntRect m_tile_rect;
    sf::VertexArray m_vertices;

    const sf::Texture* m_texture;
    sf::IntRect m_texture_rect;

    void setTexture(unsigned int gid);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif // STP_TILE_HPP
