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

#include "STP/Core/Parser.hpp"

#include <cstring>
#include <cctype>

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

#include "SFML/Graphics/PrimitiveType.hpp"
#include <zlib.h>

#include "Base64.hpp"

using namespace pugi;

namespace tmx {

Parser::Parser() : tmx_document_(), working_dir_("./") {
}

ParserStatus Parser::Load(const char* buffer, size_t size) {
    xml_parse_result result = tmx_document_.load_buffer(buffer, size);
    if (!result) return ParserStatus::LOADING_ERROR;

    xml_node map_node = tmx_document_.child("map");
    if (!map_node) return ParserStatus::INVALID_MAP_FILE;

    return ParserStatus::OK;
}

ParserStatus Parser::LoadFile(const std::string& map_file) {
    xml_parse_result result = tmx_document_.load_file(map_file.c_str());
    if (!result) return ParserStatus::LOADING_ERROR;

    xml_node map_node = tmx_document_.child("map");
    if (!map_node) return ParserStatus::INVALID_MAP_FILE;

    working_dir_ = map_file.substr(0, map_file.find_last_of('/') + 1);

    return ParserStatus::OK;
}

TileMap Parser::GetMap() {
    TileMap map;

    xml_node map_node = tmx_document_.child("map");

    // Get the map data
    // map.version_ = map_node.attribute("version").as_float();
    map.orientation_ = map_node.attribute("orientation").value();
    map.width_ = map_node.attribute("width").as_uint();
    map.height_ = map_node.attribute("height").as_uint();
    map.tilewidth_ = map_node.attribute("tilewidth").as_uint();
    map.tileheight_ = map_node.attribute("tileheight").as_uint();

    for (xml_node node : map_node.children()) {
        std::string node_name = node.name();
        // Call the respective parse function for each node
        if (node_name == "tileset") {
            std::shared_ptr<TileSet> newtileset = ParseTileSet(node, map);
            map.tilesets_.push_back(newtileset);
            map.tilesets_hash_[newtileset->GetName()] = newtileset;
        } else if (node_name == "layer") {
            Layer newlayer = ParseLayer(node, map);
            map.layers_[newlayer.GetName()] = newlayer;
            map.map_objects_.push_back(&(map.layers_[newlayer.GetName()]));
        } else if (node_name == "objectgroup") {
            ObjectGroup newobjectgroup = ParseObjectGroup(node, map);
            map.object_groups_[newobjectgroup.GetName()] = newobjectgroup;
            map.map_objects_.push_back(&(map.object_groups_[newobjectgroup.GetName()]));
        } else if (node_name == "imagelayer") {
            ImageLayer newimagelayer = ParseImageLayer(node, map);
            map.image_layers_[newimagelayer.GetName()] = newimagelayer;
            map.map_objects_.push_back(&(map.image_layers_[newimagelayer.GetName()]));
        }
    }

    // Parse the map properties
    ParseProperties(map_node, &map);

    return map;
}

std::string Parser::DecompressString(const std::string& compressed_string) {
    z_stream zstream;

    std::string outstring;

    zstream.zalloc = Z_NULL;
    zstream.zfree = Z_NULL;
    zstream.opaque = Z_NULL;
    zstream.next_in = const_cast<Bytef*>(reinterpret_cast<const Bytef*>(compressed_string.data()));
    zstream.avail_in = static_cast<uInt>(compressed_string.size());

    int result;
    result = inflateInit2(&zstream, 15 + 32);

    char outbuffer[32768];

    if (result != Z_OK) {
        return NULL;
    }

    do {
        zstream.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zstream.avail_out = sizeof(outbuffer);

        result = inflate(&zstream, Z_SYNC_FLUSH);

        switch (result) {
            case Z_NEED_DICT:
            case Z_STREAM_ERROR:
                result = Z_DATA_ERROR;
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                inflateEnd(&zstream);
                return NULL;
        }

        if (outstring.size() < zstream.total_out) {
            outstring.append(outbuffer, zstream.total_out - outstring.size());
        }
    } while (result != Z_STREAM_END);

    if (zstream.avail_in != 0) {
        return NULL;
    }

    inflateEnd(&zstream);

    return outstring;
}

void Parser::ParseProperties(xml_node& obj_node, Properties* object) {
    xml_node properties_node = obj_node.child("properties");
    if (properties_node) {
        for (const xml_node& property_node : properties_node.children("property")) {
            std::string name = property_node.attribute("name").as_string();
            std::string value = property_node.attribute("value").as_string();
            object->AddProperty(name, value);
        }
    }
}

Image Parser::ParseImage(xml_node& image_node) {
    xml_attribute attribute_source = image_node.attribute("source");
    std::string source = working_dir_ + attribute_source.as_string();

    // Check if some attributes exists in image_node
    unsigned int width = image_node.attribute("width").as_uint(0);
    unsigned int height = image_node.attribute("height").as_uint(0);
    std::string format = image_node.attribute("format").as_string("");

    int32_t trans = -1;
    xml_attribute attribute_trans = image_node.attribute("trans");
    if (attribute_trans) {
        std::stringstream ss(attribute_trans.as_string());
        ss >> std::hex >> trans;
    }

    return Image(source, width, height, trans, format);
}

std::shared_ptr<TileSet> Parser::ParseTileSet(xml_node& tileset_node, TileMap& tilemap) {
    xml_node& tileset_node_ = tileset_node;

    unsigned int firstgid = tileset_node_.attribute("firstgid").as_uint(1);

    // Check for the source attribute, load the file and get the tileset
    xml_document tsx_file;
    xml_attribute attribute_source = tileset_node_.attribute("source");
    if (attribute_source) {
        std::string source = working_dir_ + attribute_source.as_string("");
        if (!tsx_file.load_file(source.c_str())) {
            fprintf(stdout, "Error loading the XML document.\n");
        }
        tileset_node_ = tsx_file.child("tileset");
    }

    std::string name = tileset_node_.attribute("name").as_string("");
    unsigned int tilewidth = tileset_node_.attribute("tilewidth").as_uint(0);
    unsigned int tileheight = tileset_node_.attribute("tileheight").as_uint(0);
    unsigned int spacing = tileset_node_.attribute("spacing").as_uint(0);
    unsigned int margin = tileset_node_.attribute("margin").as_uint(0);
    unsigned int tilecount = tileset_node_.attribute("tilecount").as_uint(0);
    unsigned int columns = tileset_node_.attribute("columns").as_uint(0);

    // Check for the tileoffset, image childs
    Image image_data;
    sf::Vector2i tileoffset_data = {0, 0};
    for (xml_node& node : tileset_node.children()) {
        // Call the respective parse function for each node
        if (strcmp(node.name(), "tileoffset") == 0) {
            tileoffset_data.x = node.attribute("x").as_int();
            tileoffset_data.y = node.attribute("y").as_int();
        } else if (strcmp(node.name(), "image") == 0) {
            image_data = ParseImage(node);
        } else if (strcmp(node.name(), "terraintypes") == 0) {
        }
    }

    // Create the new TileSet
    std::shared_ptr<TileSet> tileset(new TileSet(
        firstgid, name, tilewidth, tileheight,
        image_data, spacing, margin, tileoffset_data
    ));

    // Parse each tile property
    for (xml_node& tile_node : tileset_node_.children("tile")) {
        unsigned int id = tile_node.attribute("id").as_uint();
        ParseProperties(tile_node, tileset->GetTile(id).properties_.get());
    }

    // Parse the tileset properties
    ParseProperties(tileset_node_, tileset.get());

    return tileset;
}

Layer Parser::ParseLayer(xml_node& layer_node, TileMap& tilemap) {
    // Get the map data
    std::string name = layer_node.attribute("name").as_string();
    unsigned int width = layer_node.attribute("width").as_uint();
    unsigned int height = layer_node.attribute("height").as_uint();
    float opacity = layer_node.attribute("opacity").as_float(1.f);
    bool visible = layer_node.attribute("visible").as_bool(true);
    int offsetx = layer_node.attribute("offsetx").as_int(0);
    int offsety = layer_node.attribute("offsety").as_int(0);

    // Create the new Layer
    Layer layer(name, width, height, opacity, visible, tilemap.GetOrientation());

    // Parse the layer properties
    ParseProperties(layer_node, &layer);

    // Parse the layer data
    std::vector<unsigned int> layer_data;
    layer_data.reserve(width * height);
    xml_node data_node = layer_node.child("data");
    if (data_node) {
        std::string data = data_node.text().as_string();

        // Remove spaces
        data.erase(std::remove_if(data.begin(), data.end(), std::isspace), data.end());

        // Check if the encoding attribute exists in data_node
        std::string encoding = data_node.attribute("encoding").as_string("");
        if (encoding == "base64") {  // Base64 encoding
            data = base64_decode(data);

            // Check if the compression attribute exists in data_node
            if (data_node.attribute("compression"))
                data = DecompressString(data);

            size_t expectedSize = width * height * 4;  // number of tiles * 4 bytes = 32bits / tile
            std::vector<unsigned char>byteVector;  // to hold decompressed data as bytes
            byteVector.reserve(expectedSize);
            for (char byte : data)
                byteVector.push_back(static_cast<unsigned char>(byte));

            for (unsigned int i = 0; i < byteVector.size() - 3; i += 4) {
                unsigned int gid = byteVector[i] |
                    byteVector[i + 1] << 8 |
                    byteVector[i + 2] << 16 |
                    byteVector[i + 3] << 24;
                layer_data.push_back(gid);
            }
        } else if (encoding == "csv") {  // CSV encoding
            std::stringstream data_stream(data);
            unsigned int gid;
            while (data_stream >> gid) {
                if (data_stream.peek() == ',')
                    data_stream.ignore();
                layer_data.push_back(gid);
            }
        } else if (encoding.empty()) {  // Unencoded
            for (const pugi::xml_node& tile_node : data_node.children("tile")) {
                unsigned int gid = tile_node.attribute("gid").as_uint();
                layer_data.push_back(gid);
            }
        }

        // Add each tile to the Layer
        sf::Vector2f tile_pos;
        unsigned int count_x = 0;
        unsigned int count_y = 0;
        unsigned int tilewidth = tilemap.GetTileWidth();
        unsigned int tileheight = tilemap.GetTileHeight();

        for (unsigned int gid : layer_data) {
            tile_pos = sf::Vector2f(
                static_cast<float>(count_x * tilewidth),
                static_cast<float>(count_y * tileheight)
            );

            unsigned int flip_flag = (gid & (TileFlip::FLIP_HORIZONTAL |
                                             TileFlip::FLIP_VERTICAL |
                                             TileFlip::FLIP_DIAGONAL));

            gid &= ~(TileFlip::FLIP_HORIZONTAL |
                     TileFlip::FLIP_VERTICAL |
                     TileFlip::FLIP_DIAGONAL);

            Tile tile_cpy;
            TileSet* tileset = tilemap.GetTileSet(gid);
            if (tileset != nullptr) {
                tile_pos.x += tileset->GetTileOffSet().x;
                tile_pos.y += tileset->GetTileOffSet().y;
                tile_cpy = tileset->GetTile(gid - tileset->GetFirstGID());

                if (tilemap.GetOrientation() != "orthogonal") {
                    int x = static_cast<int>(tile_pos.x / tilewidth);
                    int y = static_cast<int>(tile_pos.y / tileheight);

                    if (tilemap.GetOrientation() == "isometric") {
                        tile_pos.x = (x - y) * tilewidth * 0.5f;
                        tile_pos.y = (x + y) * tileheight * 0.5f;
                    } else if (tilemap.GetOrientation() == "staggered") {
                        if (y % 2 == 0) {
                            tile_pos.x = static_cast<float>(x * tilewidth);
                        } else {
                            tile_pos.x = static_cast<float>(x * tilewidth + tilewidth / 2.f);
                        }
                        tile_pos.y = static_cast<float>(y * tileheight / 2.f);
                    }
                }
            }

            tile_cpy.SetPosition(tile_pos);
            tile_cpy.SetColor(layer.color_);
            tile_cpy.Flip(flip_flag);

            layer.tiles_.push_back(std::move(tile_cpy));

            count_x = (count_x + 1) % width;
            if (count_x == 0) count_y += 1;
        }
    }

    return layer;
}

ObjectGroup Parser::ParseObjectGroup(xml_node& obj_group_node, TileMap& tilemap) {
    std::string name = obj_group_node.attribute("name").as_string("");
    unsigned int width = obj_group_node.attribute("width").as_uint(0);
    unsigned int height = obj_group_node.attribute("height").as_uint(0);

    // Check if some attributes exists in obj_group_node
    int32_t color = -1;
    xml_attribute attribute_color = obj_group_node.attribute("color");
    if (attribute_color) {
        std::string hex_string(&(attribute_color.as_string()[1]));
        // hex_string.erase(0, 1);  // Deletes the '#' character in the string
        std::stringstream ss;

        ss << hex_string;
        ss >> std::hex >> color;
    }

    float opacity = obj_group_node.attribute("opacity").as_float(1.f);
    bool visible = obj_group_node.attribute("visible").as_bool(true);

    // Create the new ObjectGroup
    ObjectGroup obj_group(name, width, height, opacity, visible, color);

    // Parse the objectgroup properties
    ParseProperties(obj_group_node, &obj_group);

    // Parse each objectgroup object
    for (xml_node& obj_node : obj_group_node.children("object")) {
        std::string obj_name = obj_node.attribute("name").as_string("");
        std::string obj_type = obj_node.attribute("type").as_string("");
        int obj_x = obj_node.attribute("x").as_int(0);
        int obj_y = obj_node.attribute("y").as_int(0);
        unsigned int obj_width = obj_node.attribute("width").as_uint(0);
        unsigned int obj_height = obj_node.attribute("height").as_uint(0);
        float obj_rotation = obj_node.attribute("rotation").as_float(0.f);
        bool obj_visible = obj_node.attribute("visible").as_bool(true);

        xml_attribute attribute_gid = obj_node.attribute("gid");
        if (attribute_gid) {
            // Tile Object
            unsigned int gid = attribute_gid.as_uint();  // Tile global id

            gid &= ~(TileFlip::FLIP_HORIZONTAL |
                     TileFlip::FLIP_VERTICAL |
                     TileFlip::FLIP_DIAGONAL);

            unsigned int id = gid - tilemap.GetTileSet(gid)->GetFirstGID();  // Tile local id

            Tile tile = tilemap.GetTileSet(gid)->GetTile(id);

            Object newobject(obj_name, obj_type, obj_x, obj_y,
                             obj_width, obj_height, obj_rotation,
                             obj_visible, ObjectType::Tile, "", tile);
            ParseProperties(obj_node, &newobject);
            obj_group.AddObject(newobject);
        } else if (obj_width && obj_height) {
            if (obj_node.child("ellipse")) {
                // Ellipse Object
               Object newobject(obj_name, obj_type, obj_x, obj_y,
                                                   obj_width, obj_height, obj_rotation,
                                                   obj_visible, ObjectType::Ellipse);
                ParseProperties(obj_node, &newobject);
                obj_group.AddObject(newobject);
            } else {
                // Rectangle Object
                Object newobject(obj_name, obj_type, obj_x, obj_y,
                                                   obj_width, obj_height, obj_rotation,
                                                   obj_visible, ObjectType::Rectangle);
                ParseProperties(obj_node, &newobject);
                obj_group.AddObject(newobject);
            }
        } else {
            xml_node polygon_node = obj_node.child("polygon");
            xml_node polyline_node = obj_node.child("polyline");
            if (polygon_node) {
                // Polygon Object
                std::string vertices_points = polygon_node.attribute("points").as_string();
                Object newobject(obj_name, obj_type, obj_x, obj_y,
                                                   obj_width, obj_height, obj_rotation,
                                                   obj_visible, ObjectType::Polygon, vertices_points);
                ParseProperties(obj_node, &newobject);
                obj_group.AddObject(newobject);
            } else if (polyline_node) {
                // Polyline Object
                std::string vertices_points = polyline_node.attribute("points").as_string();
                Object newobject(obj_name, obj_type, obj_x, obj_y,
                                                   obj_width, obj_height, obj_rotation,
                                                   obj_visible, ObjectType::Polyline, vertices_points);
                ParseProperties(obj_node, &newobject);
                obj_group.AddObject(newobject);
            }
        }
    }

    return obj_group;
}

ImageLayer Parser::ParseImageLayer(xml_node& imagelayer_node, TileMap& tilemap) {
    std::string name = imagelayer_node.attribute("name").as_string("");
    unsigned int width = imagelayer_node.attribute("width").as_uint(0);
    unsigned int height = imagelayer_node.attribute("height").as_uint(0);
    float opacity = imagelayer_node.attribute("opacity").as_float(1.f);
    bool visible = imagelayer_node.attribute("visible").as_bool(true);

    // Parse the image data
    Image image_data;
    xml_node image_node = imagelayer_node.child("image");
    if (image_node) image_data = ParseImage(image_node);

    // Create the new ImageLayer
    ImageLayer imagelayer(name, width, height, opacity, visible, image_data);

    // Parse the imagelayer properties
    ParseProperties(imagelayer_node, &imagelayer);

    return imagelayer;
}

}  // namespace tmx
