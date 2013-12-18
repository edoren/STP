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

#ifndef STP_LAYER_HPP
#define STP_LAYER_HPP

#include "STP/Config.hpp"
#include "STP/Core/Tile.hpp"
#include <string>
#include <vector>

namespace tmx {

class STP_API Layer : public sf::Drawable {
public:
    Layer(const std::string& _name, unsigned int _width, 
          unsigned int _height, float _opacity, bool _visible);
    ~Layer();

    int addTile(tmx::Tile newtile);

    bool visible;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    std::string m_name;
    unsigned int m_width, m_height;
    float m_opacity; //range 0 - 1

    std::vector< std::vector<tmx::Tile> > m_tiles;
};

}

#endif // STP_LAYER_HPP
