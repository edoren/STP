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

#include "STP/Core/TileSet.hpp"

#include <cassert>
#include <cmath>
#include <string>

namespace tmx {

TileSet::TileSet() {}

TileSet::TileSet(unsigned int firstgid, const std::string& name, unsigned int tilewidth,
                 unsigned int tileheight, tmx::Image image, unsigned int spacing,
                 unsigned int margin, sf::Vector2i tileoffset) :
        firstgid_(firstgid),
        name_(name),
        tilewidth_(tilewidth),
        tileheight_(tileheight),
        spacing_(spacing),
        margin_(margin),
        width_no_spacing_(0),
        height_no_spacing_(0),
        image_(image),
        tileoffset_(tileoffset) {
    unsigned int width_no_margin = image_.GetWidth() - (margin_ * 2);
    unsigned int height_no_margin =  image_.GetHeight() - (margin_ * 2);
    if (spacing != 0) {
        for (unsigned int i = 0; i <= width_no_margin; ++i) {
            i += tilewidth + spacing_;
            width_no_spacing_ += tilewidth;
        }
        for (unsigned int i = 0; i <= height_no_margin; ++i) {
            i += tileheight + spacing_;
            height_no_spacing_ += tileheight;
        }
    } else {
        width_no_spacing_ = width_no_margin;
        height_no_spacing_ = height_no_margin;
    }
    lastgid_ = firstgid + (width_no_spacing_ / tilewidth) * (height_no_spacing_ / tileheight) - 1;
}

TileSet::~TileSet() {}

std::string TileSet::GetName() const {
    return name_;
}

sf::IntRect TileSet::GetTextureRect(unsigned int gid) const {
    assert(gid >= firstgid_ && gid <= lastgid_);
    unsigned int local_gid, width, x, y, x_pixels,
                 y_pixels, x_spacing, y_spacing;
    local_gid = gid - firstgid_ + 1;
    width = width_no_spacing_ / tilewidth_;
    y = static_cast<unsigned int> (std::ceil(local_gid / static_cast<float>(width))) - 1;
    x = local_gid - (y * width) - 1;
    y_spacing = (spacing_ * y) + margin_;
    x_spacing = (spacing_ * x) + margin_;
    y_pixels = (y * tileheight_) + y_spacing;
    x_pixels = (x * tilewidth_) + x_spacing;
    sf::IntRect texture_rect(x_pixels, y_pixels, tilewidth_, tileheight_);
    return texture_rect;
}

const sf::Texture* TileSet::GetTexture() const {
    return image_.GetTexture();
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

unsigned int TileSet::GetLastGID() const {
    return lastgid_;
}

}  // namespace tmx
