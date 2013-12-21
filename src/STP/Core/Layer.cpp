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

#include "STP/Core/Layer.hpp"

#include <string>
#include <vector>

#include "SFML/Graphics/RenderTarget.hpp"

namespace tmx {

Layer::Layer() {}

Layer::Layer(const std::string& name, unsigned int width,
             unsigned int height, float opacity, bool visible) :
        name_(name),
        width_(width),
        height_(height),
        opacity_(opacity),
        visible(visible) {
    // Reserve space for each vector to avoid reallocate
    tiles_.reserve(height);
    for (unsigned int i = 0; i < height; ++i) {
        std::vector<tmx::Tile> newvec;
        newvec.reserve(width);
        tiles_.push_back(newvec);
    }
}

Layer::~Layer() {}

std::string Layer::GetName() const {
    return name_;
}

int Layer::AddTile(tmx::Tile newtile) {
    for (unsigned int i = 0; i < height_; ++i) {
        if (tiles_[i].size() < width_) {
            tiles_[i].push_back(newtile);
            return 0;
        }
    }
    return -1;
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (visible) {
        for (unsigned int y = 0; y < tiles_.size(); ++y) {
            for (unsigned int x = 0; x < tiles_[y].size(); ++x) {
                target.draw(tiles_[y][x]);
            }
        }
    }
}

}  // namespace tmx
