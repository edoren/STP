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

#include <string>
#include <vector>
#include <unordered_map>

#include "STP/Config.hpp"
#include "STP/Core/TileSet.hpp"
#include "STP/Core/Layer.hpp"

namespace tmx {

class STP_API TileMap : public sf::Drawable {
 public:
    TileMap();
    TileMap(float version, const std::string& orientation, unsigned int width,
            unsigned int height, unsigned int tilewidth, unsigned int tileheight);
    ~TileMap();

    void AddLayer(tmx::Layer newlayer);
    void AddTileSet(tmx::TileSet newtileset);

    // Return the tileset attached to the global id
    tmx::Layer& GetLayer(const std::string& layername);
    const tmx::TileSet* GetTileSet(unsigned int gid) const;

 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
    float version_;
    std::string orientation_;
    unsigned int width_, height_, tilewidth_, tileheight_;

    std::unordered_map<std::string, tmx::Layer*> layers_hash_;
    std::vector<tmx::Layer> layers_;
    std::vector<tmx::TileSet> tilesets_;
};

}  // namespace tmx

#endif  // STP_TILEMAP_HPP
