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

#include "STP/Core/ObjectGroup.hpp"

#include <string>
#include <vector>

#include "SFML/Graphics/RenderTarget.hpp"

namespace tmx {

ObjectGroup::ObjectGroup() {}

ObjectGroup::ObjectGroup(const std::string& name, unsigned int width, unsigned int height,
                         float opacity, bool visible, int32_t hexcolor) :
        MapObject(name, width, height, opacity, visible) {
    if (hexcolor >= 0) {
        color_.r = hexcolor >> 16;
        color_.g = (hexcolor >> 8) & 0xff;
        color_.b = hexcolor & 0xff;
    }
    color_.a = static_cast<unsigned char>(255 * opacity);
}

ObjectGroup::~ObjectGroup() {}

void ObjectGroup::AddObject(tmx::Object newobject) {
    newobject.SetColor(color_);
    objects_.push_back(newobject);
}

void ObjectGroup::SetOpacity(float opacity) {
    color_.a = static_cast<unsigned char>(255 * opacity);
    for (auto& object : objects_) {
        object.SetColor(color_);
    }
}

void ObjectGroup::SetColor(const sf::Color& color) {
    color_.r = color.r;
    color_.g = color.g;
    color_.b = color.b;
    for (auto& object : objects_) {
        object.SetColor(color_);
    }
}

void ObjectGroup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (visible) {
        for (unsigned int i = 0; i < objects_.size(); ++i)
            target.draw(objects_[i]);
    }
}

}  // namespace tmx
