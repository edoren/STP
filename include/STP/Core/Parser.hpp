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

#ifndef STP_PARSER_HPP
#define STP_PARSER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <vector>
#include <string>

#include <pugixml.hpp>

#include "STP/Config.hpp"
#include "STP/Core/Properties.hpp"
#include "STP/Core/TileMap.hpp"
#include "STP/Core/TileSet.hpp"
#include "STP/Core/Layer.hpp"
#include "STP/Core/ObjectGroup.hpp"
#include "STP/Core/ImageLayer.hpp"

using namespace pugi;

namespace tmx {

enum class ParserStatus {
    OK,               // All OK
    LOADING_ERROR,    // Used when occurs an error loading a file
    INVALID_MAP_FILE  // Used when the file is not a tiled map file
};

class Parser {
public:
    ////////////////////////////////////////////////////////////
    /// @brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Parser();

    ////////////////////////////////////////////////////////////
    /// @brief Load a Tiled map from memory
    ///
    /// @param buffer The buffer that stores the map
    /// @param size   The size of the buffer
    ///
    /// @return The loading status.
    ///
    ////////////////////////////////////////////////////////////
    ParserStatus Load(const char* buffer, size_t size);

    ////////////////////////////////////////////////////////////
    /// @brief Load a Tiled map from memory
    ///
    /// @param buffer The buffer that stores the map
    /// @param size   The size of the buffer
    ///
    /// @return The loading status.
    ///
    ////////////////////////////////////////////////////////////
    ParserStatus LoadFile(const std::string& tmx_file);

    ////////////////////////////////////////////////////////////
    /// @brief Parse the TileMap from the file previously loaded
    ///
    /// @return tmx::TileMap
    ///
    ////////////////////////////////////////////////////////////
    TileMap GetMap();

private:
    std::string DecompressString(const std::string& compressed_string);
    void AddTileToLayer(Layer* layer, int gid, sf::Vector2i tile_pos, TileMap* tilemap);

    Image ParseImage(const xml_node& image_node);
    TileSet* ParseTileSet(xml_node& tileset_node);
    Layer* ParseLayer(const xml_node& layer_node, TileMap* tilemap);
    ObjectGroup* ParseObjectGroup(const xml_node& obj_group_node, TileMap* tilemap);
    ImageLayer* ParseImageLayer(const xml_node& imagelayer_node);
    void ParseProperties(const xml_node& object_node, Properties* object);

private:
    xml_document tmx_document_;
    std::string working_dir_;
};

}  // namespace tmx

#endif  // STP_PARSER_HPP
