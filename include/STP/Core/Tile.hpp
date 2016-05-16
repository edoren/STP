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

#ifndef STP_TILE_HPP
#define STP_TILE_HPP

#include <string>
#include <vector>
#include <memory>

#include "SFML/Graphics/Vertex.hpp"
#include "SFML/Graphics/Drawable.hpp"

#include "STP/Config.hpp"
#include "STP/Core/Properties.hpp"

namespace tmx {

class Parser;
class TileSet;
class Layer;

enum TileFlip : unsigned int {
    FLIP_HORIZONTAL = 0x80000000,
    FLIP_VERTICAL = 0x40000000,
    FLIP_DIAGONAL = 0x20000000
};

class STP_API Tile : public sf::Drawable {
public:
    ////////////////////////////////////////////////////////////
    /// @brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Tile();

    ////////////////////////////////////////////////////////////
    /// @brief Constructor that receives the gid, tile_rect and a pointer to the tileset
    ///
    /// @param gid       The global id of the tmx::TileSet::Tile attached.
    /// @param tile_rect The global bounds of the tile.
    /// @param tileset   A pointer to a tmx::TileSet to get the texture.
    ///
    ////////////////////////////////////////////////////////////
    Tile(sf::Vector2f tile_pos, sf::Vector2f texture_pos = { 0.f, 0.f },
         sf::Vector2f tile_size = {0.f, 0.f}, TileSet* tileset = nullptr);

public:
    ////////////////////////////////////////////////////////////
    /// @brief Check if the tile is empty (Doesn't have a texture).
    ///
    /// @return true if the tile is empty, false otherwise.
    ///
    ////////////////////////////////////////////////////////////
    bool empty() const;

    ////////////////////////////////////////////////////////////
    /// @brief Change the Tile position
    ///
    ////////////////////////////////////////////////////////////
    void SetPosition(const sf::Vector2f& pos);

    ////////////////////////////////////////////////////////////
    /// @brief Flip the Tile in the direction specified
    ///
    ////////////////////////////////////////////////////////////
    Tile& Flip(unsigned int flags);

    ////////////////////////////////////////////////////////////
    /// @brief Return the size of the Tile
    ///
    /// @return Return the size, if empty return sf::Vector2f(0, 0)
    ///
    ////////////////////////////////////////////////////////////
    sf::Vector2f GetSize() const;

    ////////////////////////////////////////////////////////////
    /// @brief Return the texture attached to the Tile
    ///
    /// @return Return a sf::Texture, if empty return nullptr
    ///
    ////////////////////////////////////////////////////////////
    const sf::Texture* GetTexture() const;

    ////////////////////////////////////////////////////////////
    /// @brief Change the color of the tile, affect the opacity.
    ///
    /// @param color sf::Color RGBA value
    ///
    ////////////////////////////////////////////////////////////
    void SetColor(const sf::Color& color);

    ////////////////////////////////////////////////////////////
    /// @brief Add new property.
    ///
    /// @param name  The name of the property
    /// @param value The value of the property
    ///
    ////////////////////////////////////////////////////////////
    void AddProperty(const std::string& name, const std::string& value);

    ////////////////////////////////////////////////////////////
    /// @brief Return a property value given a name
    ///
    /// @param name The name of the property
    ///
    /// @return Reference to the property value
    ///
    ////////////////////////////////////////////////////////////
    std::string& GetPropertyValue(const std::string& name);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    friend TileSet;
    friend Layer;
    friend Parser;

    sf::Vertex vertices_[4];
    std::shared_ptr<Properties> properties_; // shared_ptr
    const sf::Texture* texture_;

public:
    /// @brief Visibility of the Tile
    bool visible;
};

}  // namespace tmx

#endif  // STP_TILE_HPP
