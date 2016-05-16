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
#include <memory>
#include <unordered_map>

#include "STP/Config.hpp"
#include "STP/Core/Properties.hpp"
#include "STP/Core/TileSet.hpp"
#include "STP/Core/Layer.hpp"
#include "STP/Core/ObjectGroup.hpp"
#include "STP/Core/ImageLayer.hpp"

namespace tmx {

// TODO: render order
enum class MapRenderOrder : unsigned int {
    RIGHT_DOWN,
    RIGHT_UP,
    LEFT_DOWN,
    LEFT_UP
};

enum class MapOrientation : unsigned int {
    ORTHOGONAL,
    ISOMETRIC,
    STAGGERED,
    HEXAGONAL  // TODO: support hexagonal maps
};

////////////////////////////////////////////////////////////
/// @brief Main class to manage the TMX Map Format
///
////////////////////////////////////////////////////////////
class STP_API TileMap : public sf::Drawable, public Properties {
public:
    TileMap();
    TileMap(TileMap&& other) = default;
    TileMap& operator=(TileMap&&) = default;

private:
    // TODO: Map copy constructor support
    TileMap(const TileMap& other) = delete;
    TileMap& operator=(const TileMap&) = delete;

    TileMap(MapOrientation orientation,
            MapRenderOrder renderorder,
            unsigned int width,
            unsigned int height,
            unsigned int tilewidth,
            unsigned int tileheight);

public:
    ////////////////////////////////////////////////////////////
    /// @brief Return the tile set attached to the global id
    ///
    /// @param gid The gid of the tile
    ///
    /// @return Pointer to a tmx::TileSet or nullptr if
    ///         the gid does not exist or is 0
    ///
    ////////////////////////////////////////////////////////////
    TileSet* GetTileSet(unsigned int gid);

    ////////////////////////////////////////////////////////////
    /// @brief Return the tile set given a name
    ///
    /// @param tileset_name The name of the tile set
    ///
    /// @return Pointer to a constant tmx::TileSet
    ///
    ////////////////////////////////////////////////////////////
    TileSet& GetTileSet(const std::string& tileset_name);

    ////////////////////////////////////////////////////////////
    /// @brief Return the layer based on its name
    ///
    /// @param layer_name The name of the layer
    ///
    /// @return Reference to a tmx::Layer
    ///
    ////////////////////////////////////////////////////////////
    Layer& GetLayer(const std::string& layer_name);

    ////////////////////////////////////////////////////////////
    /// @brief Return the object group based on its name
    ///
    /// @param objectgroup_name The name of the object group
    ///
    /// @return Reference to a tmx::ObjectGroup
    ///
    ////////////////////////////////////////////////////////////
    ObjectGroup& GetObjectGroup(const std::string& objectgroup_name);

    ////////////////////////////////////////////////////////////
    /// @brief Return the image layer based on its name
    ///
    /// @param imagelayer_name The name of the image layer
    ///
    /// @return Reference to a tmx::ImageLayer
    ///
    ////////////////////////////////////////////////////////////
    ImageLayer& GetImageLayer(const std::string& imagelayer_name);

    ////////////////////////////////////////////////////////////
    /// @brief Display the objects in the map
    ///
    /// @param show true to display them, false to hides them
    ///
    /// @return Reference to a tmx::ImageLayer
    ///
    ////////////////////////////////////////////////////////////
    void ShowObjects(bool show = true);

    ////////////////////////////////////////////////////////////
    /// @brief Return the map width
    ///
    /// @return unsigned int value
    ///
    ////////////////////////////////////////////////////////////
    unsigned int GetWidth() const;

    ////////////////////////////////////////////////////////////
    /// @brief Return the map height
    ///
    /// @return unsigned int value
    ///
    ////////////////////////////////////////////////////////////
    unsigned int GetHeight() const;

    ////////////////////////////////////////////////////////////
    /// @brief Return the tile width
    ///
    /// @return unsigned int value
    ///
    ////////////////////////////////////////////////////////////
    unsigned int GetTileWidth() const;

    ////////////////////////////////////////////////////////////
    /// @brief Return the tile height
    ///
    /// @return unsigned int value
    ///
    ////////////////////////////////////////////////////////////
    unsigned int GetTileHeight() const;

    ////////////////////////////////////////////////////////////
    /// @brief Return the orientation of the map
    ///
    /// @return The orienation of the map as MapOrientation
    ///
    ////////////////////////////////////////////////////////////
    MapOrientation GetOrientation() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    friend class Parser;

    MapOrientation orientation_;
    MapRenderOrder renderorder_;
    unsigned int width_;
    unsigned int height_;
    unsigned int tilewidth_;
    unsigned int tileheight_;

    std::unordered_map<std::string, Layer> layers_;
    std::unordered_map<std::string, ObjectGroup> object_groups_;
    std::unordered_map<std::string, ImageLayer> image_layers_;
    std::vector<MapObject*> map_objects_;

    std::vector<std::shared_ptr<TileSet>> tilesets_;
    std::unordered_map<std::string, std::shared_ptr<TileSet>> tilesets_hash_;
};

}  // namespace tmx
