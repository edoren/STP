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

#include "STP/Core/Object.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <cmath>

#include "SFML/Graphics/RenderTarget.hpp"

namespace tmx {

Object::Object(const std::string& name, const std::string& type, int x, int y,
               unsigned int width, unsigned int height, float rotation, bool visible,
               tmx::ObjectType shape_type, const std::string& vertices_points) :
        name_(name),
        type_(type),
        x_(x),
        y_(y),
        width_(width),
        height_(height),
        rotation_(rotation),
        visible(visible) {
    float left = static_cast<float>(x);
    float top = static_cast<float>(y);
    float l_width = static_cast<float>(width);
    float l_height = static_cast<float>(height);

    if (shape_type == tmx::Polygon || shape_type == tmx::Polyline) {
        if (!vertices_points.empty()) {
            std::stringstream sstream(vertices_points);
            float x_pos, y_pos;
            while (sstream >> x_pos) {
                if (sstream.peek() == ',')
                    sstream.ignore();
                sstream >> y_pos;
                vertices_.push_back(sf::Vertex(sf::Vector2f(x_pos + left, y_pos + top)));
            }
            if (shape_type == tmx::Polygon)
                vertices_.push_back(vertices_[0]);  // Add the last line to close the polygon
        }
    } else if (shape_type == tmx::Rectangle) {
        vertices_.push_back(sf::Vertex(sf::Vector2f(left, top)));
        vertices_.push_back(sf::Vertex(sf::Vector2f(left + l_width, top)));
        vertices_.push_back(sf::Vertex(sf::Vector2f(left + l_width, top + l_height)));
        vertices_.push_back(sf::Vertex(sf::Vector2f(left, top + l_height)));
        vertices_.push_back(sf::Vertex(sf::Vector2f(left, top)));  // Add the last line to close the rectangle
    } else if (shape_type == tmx::Ellipse) {
        const float PI = 3.14159265358979f;
        float a = l_width / 2.f;
        float b = l_height / 2.f;
        float x, y;  // x and y global coordinates
        sf::Vector2f center(left + a, top + b);
        float partitions = pow(2.f, 3.f + ceil((a + b) / 30));
        float angle_increment = 360.f / partitions;
        for (int i = 0; i * angle_increment <= 360.f; ++i) {
            x = center.x + a * cos((i * angle_increment) * PI / 180.f);
            y = center.y + b * sin((i * angle_increment) * PI / 180.f);
            vertices_.push_back(sf::Vertex(sf::Vector2f(x, y)));
        }
    }
}

Object::~Object() {}

void Object::SetColor(const sf::Color& color) {
    for (auto& vertice : vertices_) {
        vertice.color = color;
    }
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (visible) {
        target.draw(&vertices_[0], vertices_.size(), sf::LinesStrip);
    }
}

}  // namespace tmx
