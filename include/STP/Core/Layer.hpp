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

#pragma once

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <string>
#include <vector>

#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/Drawable.hpp"

#include "STP/Config.hpp"
#include "STP/Core/TileSet.hpp"
#include "STP/Core/MapObject.hpp"

namespace tmx {

////////////////////////////////////////////////////////////
/// @brief Class for manage the TMX Layers
///
////////////////////////////////////////////////////////////
class STP_API Layer : public MapObject {
public:
    ////////////////////////////////////////////////////////////
    /// @brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Layer();

private:
    ////////////////////////////////////////////////////////////
    /// @brief Constructs a layer given a name, width, height,
    ///        opacity and visible attributes
    ///
    /// @param name    The name of the layer
    /// @param width   The width of the layer in tiles
    /// @param height  The height of the layer in tiles
    /// @param opacity Float value between 0.0 to 1.0
    /// @param visible The visibility of the layer
    ///
    ////////////////////////////////////////////////////////////
    Layer(const std::string& name, unsigned int width,
          unsigned int height, float opacity, bool visible,
          std::string orientation);

public:
    ////////////////////////////////////////////////////////////
    /// @brief Returns the width in tiles.
    ///
    /// @return The width of the layer in tiles.
    ///
    ////////////////////////////////////////////////////////////
    unsigned int GetWidth() const;

    ////////////////////////////////////////////////////////////
    /// @brief Returns the height in tiles.
    ///
    /// @return The height of the layer in tiles.
    ///
    ////////////////////////////////////////////////////////////
    unsigned int GetHeight() const;

    ////////////////////////////////////////////////////////////
    /// @brief Get the tile given a coordinate. Left-Up tile is (0, 0).
    ///
    /// @param x The x position of the Tile
    /// @param y The y position of the Tile
    ///
    /// @exception std::out_of_range If no tile within the range of the layer.
    ///
    /// @return Reference to the Tile.
    ///
    ////////////////////////////////////////////////////////////
    Tile& GetTile(unsigned int x, unsigned int y);

    ////////////////////////////////////////////////////////////
    /// @brief Change the color of the layer, does not affect the opacity
    ///
    /// @param color sf::Color RGB value
    ///
    ////////////////////////////////////////////////////////////
    void SetColor(const sf::Color& color);

    ////////////////////////////////////////////////////////////
    /// @brief Change the opacity of the layer
    ///
    /// @param opacity Float value between 0.0 to 1.0
    ///
    ////////////////////////////////////////////////////////////
    void SetOpacity(float opacity);

private:
    friend class Parser;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Tile> tiles_;
    std::string orientation_;
};

}  // namespace tmx
