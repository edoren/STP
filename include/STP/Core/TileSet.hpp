////////////////////////////////////////////////////////////
//
// The MIT License (MIT)
//
// STP - SFML TMX Parser
// Copyright (c) 2013-2014 Manuel Sabogal
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

#include <string>

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"

#include "STP/Config.hpp"
#include "STP/Core/Properties.hpp"
#include "STP/Core/Image.hpp"

namespace tmx {

class STP_API TileSet : public tmx::Properties {
 public:
    class Tile : public tmx::Properties {  // 0.2
        unsigned int gid;
    };

    struct TerrainTypes {  // 0.2
    };

 public:
    TileSet();
    TileSet(unsigned int firstgid, const std::string& name, unsigned int tilewidth,
            unsigned int tileheight, tmx::Image image, unsigned int spacing = 0,
            unsigned int margin = 0, sf::Vector2i tileoffset = {0, 0});

    ~TileSet();

    sf::IntRect GetTextureRect(unsigned int gid) const;
    const sf::Texture* GetTexture() const;
    const sf::Vector2i GetTileOffSet() const;

    std::string GetName() const;

    unsigned int GetTileWidth() const;
    unsigned int GetTileHeight() const;
    unsigned int GetFirstGID() const;
    unsigned int GetLastGID() const;

 private:
    unsigned int firstgid_, lastgid_;
    std::string name_;
    unsigned int tilewidth_, tileheight_, spacing_, margin_;
    unsigned int width_no_spacing_, height_no_spacing_;
    tmx::Image image_;
    sf::Vector2i tileoffset_;
};

}  // namespace tmx

#endif  // STP_TILESET_HPP
