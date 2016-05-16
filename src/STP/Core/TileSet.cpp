////////////////////////////////////////////////////////////
//
// The MIT License (MIT)
//
// STP - SFML TMX Parser
// Copyright (c) 2013-2016 Manuel Sabogal
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

#include "STP/Core/TileSet.hpp"

#include <stdexcept>
#include <cmath>
#include <string>

namespace tmx {

TileSet::TileSet() :
        firstgid_(0),
        tilewidth_(0),
        tileheight_(0),
        spacing_(0),
        margin_(0),
        tileoffset_(0, 0) {
}

TileSet::TileSet(const TileSet & other) :
        firstgid_(other.firstgid_),
        name_(other.name_),
        tilewidth_(other.tilewidth_),
        tileheight_(other.tileheight_),
        spacing_(other.spacing_),
        margin_(other.margin_),
        image_(other.image_),
        tileoffset_(other.tileoffset_),
        tiles_(other.tiles_) {
    for (auto& tile : tiles_) {
        tile.texture_ = image_.GetTexture();
    }
}

TileSet::TileSet(unsigned int firstgid, const std::string& name, unsigned int tilewidth,
                 unsigned int tileheight, Image image, unsigned int spacing,
                 unsigned int margin, sf::Vector2i tileoffset) :
        firstgid_(firstgid),
        name_(name),
        tilewidth_(tilewidth),
        tileheight_(tileheight),
        spacing_(spacing),
        margin_(margin),
        image_(image),
        tileoffset_(tileoffset) {
    columns_ = (image_.GetWidth() - (margin_ * 2) + spacing_) / (tilewidth_ + spacing_);
    unsigned int rows = (image_.GetHeight() - (margin_ * 2) + spacing_) / (tileheight_ + spacing_);
    // Add each tile to the TileSet
    tilecount_ = columns_ * rows;
    sf::Vector2f texture_pos;
    tiles_.reserve(tilecount_);
    for (unsigned int i = 0; i < tilecount_; ++i) {
        texture_pos.x = static_cast<float>((i % columns_) * (tilewidth_ + spacing_) + margin_);
        texture_pos.y = static_cast<float>((i / columns_) * (tileheight_ + spacing_) + margin_);

        tiles_.emplace_back(sf::Vector2f(0.f, 0.f), sf::Vector2f(texture_pos), sf::Vector2f(tilewidth_, tileheight_), this);
    }
}

Tile& TileSet::GetTile(unsigned int id) {
    if (id >= tiles_.size()) {
        char error[100];
        sprintf(error, "Error: tile local id %u out of range.\n", id);
        throw std::out_of_range(error);
    }
    return tiles_[id];
}

const sf::Texture* TileSet::GetTexture() const {
    return image_.GetTexture();
}

const std::string& TileSet::GetName() const {
    return name_;
}

const sf::Vector2i TileSet::GetTileOffSet() const {
    return tileoffset_;
}

unsigned int TileSet::GetTileWidth() const {
    return tilewidth_;
}

unsigned int TileSet::GetTileHeight() const {
    return tileheight_;
}

unsigned int TileSet::GetFirstGID() const {
    return firstgid_;
}

}  // namespace tmx
