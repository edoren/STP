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

#ifndef STP_OBJECT_HPP
#define STP_OBJECT_HPP

#include <string>
#include <vector>
#include <unordered_map>

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Drawable.hpp"

#include "STP/Config.hpp"
#include "STP/Core/Properties.hpp"

namespace tmx {

enum ObjectType { Rectangle, Ellipse, Polygon, Polyline };

class STP_API Object : public sf::Drawable, public tmx::Properties {
 public:
    Object(const std::string& name, const std::string& type, int x, int y,
           unsigned int width, unsigned int height, float rotation, bool visible,
           tmx::ObjectType shape_type, const std::string& vertices_points = std::string());
    ~Object();

    void SetColor(const sf::Color& color);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
    std::string name_;
    std::string type_;
    unsigned int x_, y_;
    unsigned int width_, height_;
    float rotation_;

    std::vector<sf::Vertex> vertices_;

 public:
    bool visible;
};

}  // namespace tmx

#endif  // STP_OBJECT_HPP
