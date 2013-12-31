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

#include "STP/Core/TileSet.hpp"

#include <cassert>
#include <cmath>
#include <string>

namespace tmx {

TileSet::TileSet() {}

TileSet::TileSet(unsigned int firstgid, const std::string& name, unsigned int tilewidth,
                 unsigned int tileheight, unsigned int spacing, unsigned int margin,
                 tmx::Image image, tmx::TileSet::TileOffSet tileoffset) :
        firstgid_(firstgid),
        name_(name),
        tilewidth_(tilewidth),
        tileheight_(tileheight),
        spacing_(spacing),
        margin_(margin),
        image_(image),
        tileoffset_(tileoffset) {
    lastgid_ = firstgid + (image.GetWidth() / tilewidth) * (image.GetHeight() / tileheight) - 1;
}

TileSet::~TileSet() {}

// Struct default constructors
TileSet::TileOffSet::TileOffSet() : x(0), y(0) {}

std::string TileSet::GetName() const {
    return name_;
}

sf::IntRect TileSet::GetTextureRect(unsigned int gid) const {
    assert(gid >= firstgid_ && gid <= lastgid_);
    int local_gid, width, x, y, x_pixels, y_pixels;
    local_gid = gid - firstgid_ + 1;
    width = image_.GetWidth() / tilewidth_;
    y = static_cast<int> (std::ceil(local_gid / static_cast<float>(width)));
    x = local_gid - ((y - 1) * width);
    y_pixels = (y - 1) * tilewidth_;
    x_pixels = (x - 1) * tileheight_;
    sf::IntRect tilerect(x_pixels, y_pixels, tilewidth_, tileheight_);
    return tilerect;
}

const sf::Texture* TileSet::GetTexture() const {
    return image_.GetTexture();
}

unsigned int TileSet::GetFirstGID() const {
    return firstgid_;
}

unsigned int TileSet::GetLastGID() const {
    return lastgid_;
}

}  // namespace tmx
