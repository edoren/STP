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

#ifndef STP_OBJECTGROUP_HPP
#define STP_OBJECTGROUP_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "STP/Config.hpp"
#include "STP/Core/MapObject.hpp"
#include "STP/Core/Object.hpp"

namespace tmx {

class STP_API ObjectGroup : public MapObject {
 public:
    ObjectGroup();
    ObjectGroup(const std::string& name, unsigned int width, unsigned int height,
                float opacity, bool visible, int32_t hexcolor = -1);
    ~ObjectGroup();

    void AddObject(tmx::Object newobject);

    void SetOpacity(float opacity);
    void SetColor(const sf::Color& color);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
    std::vector<tmx::Object> objects_;
};

}  // namespace tmx

#endif  // STP_OBJECTGROUP_HPP
