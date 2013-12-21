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

#include "STP/Core/Parser.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Base64.hpp"

namespace tmx {

Parser::Parser() {}

Parser::~Parser() {}

tmx::TileMap Parser::ParseFile(const std::string &file_to_parse) {
    pugi::xml_document tmx_file;

    if (!tmx_file.load_file(file_to_parse.c_str())) {
        std::cerr << "Error loading the XML document." << std::endl;
    }

    pugi::xml_node map_node;

    if (!(map_node = tmx_file.child("map"))) {
        std::cerr << "The document is not a valid TMX file." << std::endl;
    }

    working_dir_ = file_to_parse.substr(0, file_to_parse.find_last_of('/') + 1);

    float version;
    std::string orientation;
    // Get the map data
    version = map_node.attribute("version").as_float();
    orientation = map_node.attribute("orientation").value();
    width_ = map_node.attribute("width").as_uint();
    height_ = map_node.attribute("height").as_uint();
    tilewidth_ = map_node.attribute("tilewidth").as_uint();
    tileheight_ = map_node.attribute("tileheight").as_uint();

    tmx::TileMap map(version, orientation, width_, height_, tilewidth_, tileheight_);

    tilemap_ = &map;

    for (pugi::xml_node node = map_node.first_child(); node; node = node.next_sibling()) {
        std::string node_name = node.name();
        // Call the respective parse function for each node
        if (node_name == "tileset") {
            tmx::TileSet newtileset = this->ParseTileSet(node);
            map.AddTileSet(newtileset);
        } else if (node_name == "layer") {
            tmx::Layer newlayer = this->ParseLayer(node);
            map.AddLayer(newlayer);
        } else if (node_name == "objectgroup") {
        }
    }

    return map;
}

tmx::TileSet Parser::ParseTileSet(const pugi::xml_node& tileset_node) {
    unsigned int firstgid, tilewidth, tileheight, spacing = 0, margin = 0;
    std::string name;
    struct tmx::TileSet::Image image_data;
    struct tmx::TileSet::TileOffSet tileoffset_data;

    // Get the map data
    firstgid = tileset_node.attribute("firstgid").as_uint();
    name = tileset_node.attribute("name").as_string();
    tilewidth = tileset_node.attribute("tilewidth").as_uint();
    tileheight = tileset_node.attribute("tileheight").as_uint();
    if (pugi::xml_attribute attribute_spacing = tileset_node.attribute("spacing"))
        spacing = attribute_spacing.as_uint();
    if (pugi::xml_attribute attribute_margin = tileset_node.attribute("margin"))
        margin = attribute_margin.as_uint();

    for (pugi::xml_node node = tileset_node.first_child(); node; node = node.next_sibling()) {
        std::string node_name = node.name();
        // Call the respective parse function for each node
        if (node_name == "tileoffset") {
            tileoffset_data.x = node.attribute("x").as_uint();
            tileoffset_data.y = node.attribute("y").as_uint();
        } else if (node_name == "image") {
            image_data.source = working_dir_ + node.attribute("source").as_string();
            image_data.width = node.attribute("width").as_uint();
            image_data.height = node.attribute("height").as_uint();
            if (pugi::xml_attribute attribute_trans = node.attribute("trans"))
                image_data.trans = attribute_trans.as_uint();
        } else if (node_name == "terraintypes") {
        } else if (node_name == "tile") {
        }
    }

    tmx::TileSet tileset(firstgid, name, tilewidth, tileheight, spacing, margin, image_data, tileoffset_data);

    return tileset;
}

tmx::Layer Parser::ParseLayer(const pugi::xml_node& layer_node) {
    std::string name;
    float opacity = 1.f;  // range 0 - 1
    bool visible = true;

    unsigned int count_x = 0;
    unsigned int count_y = 0;

    sf::IntRect tile_rect;

    // Get the map data
    name = layer_node.attribute("name").as_string();
    // Check if the opacity attribute exists in layer_node
    if (pugi::xml_attribute attribute_opacity = layer_node.attribute("opacity"))
        opacity = attribute_opacity.as_float();
    // Check if the visible attribute exists in layer_node
    if (pugi::xml_attribute attribute_visible = layer_node.attribute("visible"))
        visible = attribute_visible.as_bool();

    tmx::Layer layer(name, width_, height_, opacity, visible);

    if (pugi::xml_node data_node = layer_node.child("data")) {
        std::string data = data_node.text().as_string();
        // Check if the encoding attribute exists in data_node
        if (pugi::xml_attribute attribute_encoding = data_node.attribute("encoding")) {
            std::string encoding = attribute_encoding.as_string();

            if (encoding == "base64") {  // Base64 encoding
                std::stringstream ss;
                ss << data;
                ss >> data;
                data = base64_decode(data);

                int expectedSize = width_ * height_ * 4;  // number of tiles * 4 bytes = 32bits / tile
                std::vector<unsigned char>byteVector;  // to hold decompressed data as bytes
                byteVector.reserve(expectedSize);

                // Check if the compression attribute exists in data_node
                if (pugi::xml_attribute attribute_compression = data_node.attribute("compression")) {
                    std::string compression = attribute_compression.as_string();
                    //
                    //
                    //
                } else {
                    for (std::string::iterator i = data.begin(); i != data.end(); ++i)
                        byteVector.push_back(*i);
                }

                for (unsigned int i = 0; i < byteVector.size() - 3 ; i += 4) {
                    if (count_x < width_) {
                        tile_rect = sf::IntRect(count_x++ * tilewidth_, count_y * tilewidth_, tilewidth_, tileheight_);
                    } else {
                        count_x = 0;
                        tile_rect = sf::IntRect(count_x++ * tilewidth_, ++count_y * tilewidth_, tilewidth_, tileheight_);
                    }
                    int gid = byteVector[i] | byteVector[i + 1] << 8 | byteVector[i + 2] << 16 | byteVector[i + 3] << 24;
                    this->AddTile(layer, gid, tile_rect);
                }
            } else if (encoding == "csv") {  // CSV encoding
                std::stringstream data_stream(data);
                unsigned int gid;
                while (data_stream >> gid) {
                    if (count_x < width_) {
                        tile_rect = sf::IntRect(count_x++ * tilewidth_, count_y * tilewidth_, tilewidth_, tileheight_);
                    } else {
                        count_x = 0;
                        tile_rect = sf::IntRect(count_x++ * tilewidth_, ++count_y * tilewidth_, tilewidth_, tileheight_);
                    }
                    if (data_stream.peek() == ',')
                        data_stream.ignore();
                    this->AddTile(layer, gid, tile_rect);
                }
            }
        } else {  // Unencoded
            for (pugi::xml_node tile_node = data_node.first_child(); tile_node; tile_node = tile_node.next_sibling("tile")) {
                if (count_x < width_) {
                    tile_rect = sf::IntRect(count_x++ * tilewidth_, count_y * tilewidth_, tilewidth_, tileheight_);
                } else {
                    count_x = 0;
                    tile_rect = sf::IntRect(count_x++ * tilewidth_, ++count_y * tilewidth_, tilewidth_, tileheight_);
                }
                int gid = tile_node.attribute("gid").as_uint();
                this->AddTile(layer, gid, tile_rect);
            }
        }
    }

    return layer;
}

void Parser::AddTile(tmx::Layer& layer, int gid, sf::IntRect tile_rect) {
    static int i = 0;
    i++;
    const tmx::TileSet* tileset = tilemap_->GetTileSet(gid);
    tmx::Tile newtile;
    if (tileset != NULL)
        newtile = tmx::Tile(gid, tile_rect, tileset->GetTexture(), tileset->GetTextureRect(gid));
    else
        newtile = tmx::Tile(gid, tile_rect, NULL);
    layer.AddTile(newtile);
}

}  // namespace tmx
