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

#ifndef STP_IMAGE_HPP
#define STP_IMAGE_HPP

#include <string>
#include <vector>

#include "SFML/Graphics/Image.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "STP/Config.hpp"

namespace tmx {

class STP_API Image {
 public:
    Image();
    Image(const std::string& source, unsigned int width, unsigned int height,
          int32_t trans = -1, const std::string& format = std::string());
    ~Image();

 public:
    const std::string& GetSource() const;
    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    const sf::Texture* GetTexture() const;

 private:
    std::string source_;
    int32_t trans_;
    unsigned int width_, height_;
    std::string format_;
    sf::Texture texture_;
};

}  // namespace tmx

#endif  // STP_IMAGE_HPP
