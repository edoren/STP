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

#include <cassert>
#include <iostream>
#include <string>

#include "SFML/Graphics/RenderTarget.hpp"

namespace tmx {

TileMap::TileMap() {}

TileMap::TileMap(float version, const std::string& orientation, unsigned int width,
                 unsigned int height, unsigned int tilewidth, unsigned int tileheight) :
        version_(version),
        orientation_(orientation),
        width_(width),
        height_(height),
        tilewidth_(tilewidth),
        tileheight_(tileheight) {
}

TileMap::~TileMap() {}

void TileMap::AddLayer(tmx::Layer newlayer) {
    layers_.push_back(newlayer);
    layers_hash_[newlayer.GetName()] = &layers_[layers_.size()-1];
}

void TileMap::AddTileSet(tmx::TileSet newtileset) {
    tilesets_.push_back(newtileset);
}

tmx::Layer& TileMap::GetLayer(const std::string& layername) {
    auto iterator = layers_hash_.find(layername);
    if (iterator == layers_hash_.end()) {
        std::cerr << "Layer \"" << layername << "\" not found." << std::endl;
        exit(0);
    } else {
        return *iterator->second;
    }
}

const tmx::TileSet* TileMap::GetTileSet(unsigned int gid) const {
    if (gid == 0) return NULL;
    for (unsigned int i = 0; i < tilesets_.size(); ++i) {
        if (gid >= tilesets_[i].GetFirstGID() && gid <= tilesets_[i].GetLastGID())
            return &tilesets_[i];
    }
    return NULL;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (unsigned int i = 0; i < layers_.size(); ++i) {
        if (layers_[i].visible == true)
            target.draw(layers_[i]);
    }
}

}  // namespace tmx
