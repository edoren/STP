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

#ifndef STP_TILEMAP_HPP
#define STP_TILEMAP_HPP

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

class STP_API TileMap : public sf::Drawable, public tmx::Properties {
 public:
    explicit TileMap(const std::string& tmx_file);
    ~TileMap();

 private:
    TileMap(const TileMap& other) = delete;
    TileMap& operator =(const TileMap&) = delete;

 public:
    // Return the tileset attached to the global id
    const tmx::TileSet* GetTileSet(unsigned int gid) const;
    tmx::Layer& GetLayer(const std::string& layername);
    tmx::ObjectGroup& GetObjectGroup(const std::string& objectgroup_name);
    tmx::ImageLayer& GetImageLayer(const std::string& imagelayer_name);

    void ShowObjects(bool show = true);

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    unsigned int GetTileWidth() const;
    unsigned int GetTileHeight() const;

 private:
    void AddLayer(tmx::Layer* newlayer);
    void AddObjectGroup(tmx::ObjectGroup* newobjectgroup);
    void AddImageLayer(tmx::ImageLayer* newimagelayer);
    void AddTileSet(tmx::TileSet* newtileset);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
    std::string working_dir_;

    float version_;
    std::string orientation_;
    unsigned int width_, height_, tilewidth_, tileheight_;

    std::unordered_map<std::string, tmx::Layer*> layers_;
    std::unordered_map<std::string, tmx::ObjectGroup*> object_groups_;
    std::unordered_map<std::string, tmx::ImageLayer*> image_layers_;
    std::vector<std::unique_ptr<tmx::MapObject>> map_objects_;

    std::vector<std::unique_ptr<tmx::TileSet>> tilesets_;
};

}  // namespace tmx

#endif  // STP_TILEMAP_HPP
