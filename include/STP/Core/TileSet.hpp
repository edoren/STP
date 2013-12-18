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

#ifndef STP_TILESET_HPP
#define STP_TILESET_HPP

#include "STP/Config.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <string>

namespace tmx {

class STP_API TileSet {
public:
    struct tileoffset { // 0.2
        int x, y;
        tileoffset();
    };

    struct image {
        int format;
        std::string source, trans; // trans 0.2
        unsigned int width, height;
        image();
    };

    struct terraintypes { // 0.2
    };

    struct layer { // 0.2
    };

public:
    TileSet(unsigned int firstgid, const std::string& name, unsigned int tilewidth,
            unsigned int tileheight, unsigned int spacing, unsigned int margin,
            tmx::TileSet::image image, tmx::TileSet::tileoffset tileoffset);

    ~TileSet();

    sf::IntRect getTextureRect(unsigned int gid);
    const sf::Texture* getTexture();

    unsigned int getFirstGID();
    unsigned int getLastGID();

private:
    unsigned int m_firstgid, m_lastgid;
    std::string m_name;
    unsigned int m_tilewidth, m_tileheight, m_spacing, m_margin; // spacing, margin - 0.2
    struct tmx::TileSet::image m_image;
    struct tmx::TileSet::tileoffset m_tileoffset;
    sf::Texture m_texture;
};

}

#endif // STP_TILESET_HPP
