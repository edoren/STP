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

#include "Parser.hpp"

#include <string>
#include <sstream>
#include <vector>

#include "SFML/Graphics/PrimitiveType.hpp"

#include "Base64.hpp"

namespace tmx {

tmx::TileSet* ParseTileSet(const pugi::xml_node& tileset_node, const std::string& working_dir) {
    unsigned int firstgid, tilewidth, tileheight, spacing = 0, margin = 0;
    std::string name;
    tmx::TileSet::Image image_data;
    tmx::TileSet::TileOffSet tileoffset_data;

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
            tileoffset_data.x = node.attribute("x").as_int();
            tileoffset_data.y = node.attribute("y").as_int();
        } else if (node_name == "image") {
            image_data.source = working_dir + node.attribute("source").as_string();
            image_data.width = node.attribute("width").as_uint();
            image_data.height = node.attribute("height").as_uint();
            if (pugi::xml_attribute attribute_trans = node.attribute("trans"))
                image_data.trans = attribute_trans.as_uint();
        } else if (node_name == "terraintypes") {
        } else if (node_name == "tile") {
        }
    }

    // Create the new TileSet
    tmx::TileSet* tileset = new tmx::TileSet(firstgid, name, tilewidth, tileheight, spacing, margin, image_data, tileoffset_data);

    return tileset;
}

void AddTile(tmx::Layer* layer, int gid, sf::IntRect tile_rect, const tmx::TileMap* tilemap) {
    const tmx::TileSet* tileset = tilemap->GetTileSet(gid);
    tmx::Tile newtile;
    if (tileset != NULL)
        newtile = tmx::Tile(gid, tile_rect, tileset->GetTexture(), tileset->GetTextureRect(gid));
    else
        newtile = tmx::Tile(gid, tile_rect, NULL);
    layer->AddTile(newtile);
}

tmx::Layer* ParseLayer(const pugi::xml_node& layer_node, const tmx::TileMap* tilemap) {
    std::string name;
    unsigned int width, height;
    float opacity = 1.f;  // range 0 - 1
    bool visible = true;

    unsigned int count_x = 0;
    unsigned int count_y = 0;

    unsigned int tilewidth = tilemap->GetTileWidth();
    unsigned int tileheight = tilemap->GetTileHeight();

    sf::IntRect tile_rect;

    // Get the map data
    name = layer_node.attribute("name").as_string();
    width = layer_node.attribute("width").as_uint();
    height = layer_node.attribute("height").as_uint();
    // Check if the opacity attribute exists in layer_node
    if (pugi::xml_attribute attribute_opacity = layer_node.attribute("opacity"))
        opacity = attribute_opacity.as_float();
    // Check if the visible attribute exists in layer_node
    if (pugi::xml_attribute attribute_visible = layer_node.attribute("visible"))
        visible = attribute_visible.as_bool();

    // Create the new Layer
    tmx::Layer* layer = new tmx::Layer(name, width, height, opacity, visible);

    // Parse the layer properties
    if (pugi::xml_node properties_node = layer_node.child("properties")) {
        for (pugi::xml_node property_node : properties_node.children("property")) {
            std::string name = property_node.attribute("name").as_string();
            std::string value = property_node.attribute("value").as_string();
            layer->AddProperty(name, value);
        }
    }

    // Parse the layer data
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

                int expectedSize = width * height * 4;  // number of tiles * 4 bytes = 32bits / tile
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
                    if (count_x < width) {
                        tile_rect = sf::IntRect(count_x++ * tilewidth, count_y * tilewidth, tilewidth, tileheight);
                    } else {
                        count_x = 0;
                        tile_rect = sf::IntRect(count_x++ * tilewidth, ++count_y * tilewidth, tilewidth, tileheight);
                    }
                    int gid = byteVector[i] | byteVector[i + 1] << 8 | byteVector[i + 2] << 16 | byteVector[i + 3] << 24;
                    AddTile(layer, gid, tile_rect, tilemap);
                }
            } else if (encoding == "csv") {  // CSV encoding
                std::stringstream data_stream(data);
                unsigned int gid;
                while (data_stream >> gid) {
                    if (count_x < width) {
                        tile_rect = sf::IntRect(count_x++ * tilewidth, count_y * tilewidth, tilewidth, tileheight);
                    } else {
                        count_x = 0;
                        tile_rect = sf::IntRect(count_x++ * tilewidth, ++count_y * tilewidth, tilewidth, tileheight);
                    }
                    if (data_stream.peek() == ',')
                        data_stream.ignore();
                    AddTile(layer, gid, tile_rect, tilemap);
                }
            }
        } else {  // Unencoded
            for (pugi::xml_node tile_node = data_node.first_child(); tile_node; tile_node = tile_node.next_sibling("tile")) {
                if (count_x < width) {
                    tile_rect = sf::IntRect(count_x++ * tilewidth, count_y * tilewidth, tilewidth, tileheight);
                } else {
                    count_x = 0;
                    tile_rect = sf::IntRect(count_x++ * tilewidth, ++count_y * tilewidth, tilewidth, tileheight);
                }
                int gid = tile_node.attribute("gid").as_uint();
                AddTile(layer, gid, tile_rect, tilemap);
            }
        }
    }

    return layer;
}

void AddObjectProperties(pugi::xml_node object_node, tmx::Object* object) {
    if (pugi::xml_node properties_node = object_node.child("properties")) {
        for (pugi::xml_node property_node : properties_node.children("property")) {
            std::string name = property_node.attribute("name").as_string();
            std::string value = property_node.attribute("value").as_string();
            object->AddProperty(name, value);
        }
    }
}

tmx::ObjectGroup* ParseObjectGroup(const pugi::xml_node& object_group_node) {
    std::string name;
    uint32_t color;
    unsigned int width, height;
    float opacity = 1.f;
    bool visible = true;

    name = object_group_node.attribute("name").as_string();
    width = object_group_node.attribute("width").as_uint();
    height = object_group_node.attribute("height").as_uint();

    // Check if the color attribute exists in object_group_node
    if (pugi::xml_attribute attribute_color = object_group_node.attribute("color")) {
        std::string hex_string(attribute_color.as_string());
        hex_string.erase(0, 1);  // Deletes the '#' character in the string
        std::stringstream ss;

        ss << hex_string;
        ss >> std::hex >> color;
    }
    // Check if the opacity attribute exists in object_group_node
    if (pugi::xml_attribute attribute_opacity = object_group_node.attribute("opacity"))
        opacity = attribute_opacity.as_float();
    // Check if the visible attribute exists in object_group_node
    if (pugi::xml_attribute attribute_visible = object_group_node.attribute("visible"))
        visible = attribute_visible.as_bool();

    // Create the new ObjectGroup
    tmx::ObjectGroup* object_group = new tmx::ObjectGroup(name, width, height, opacity,
                                                          visible, color);

    // Parse the objectgroup properties
    if (pugi::xml_node properties_node = object_group_node.child("properties")) {
        for (pugi::xml_node property_node : properties_node.children("property")) {
            std::string name = property_node.attribute("name").as_string();
            std::string value = property_node.attribute("value").as_string();
            object_group->AddProperty(name, value);
        }
    }

    // Parse each objectgroup object
    for (pugi::xml_node object_node : object_group_node.children("object")) {
        std::string object_name;
        std::string object_type;
        int object_x, object_y;
        unsigned int object_width = 0, object_height = 0;
        float object_rotation = 0;
        bool object_visible = true;

        object_x = object_node.attribute("x").as_int();
        object_y = object_node.attribute("y").as_int();

        // Check if the name attribute exists in object_node
        if (pugi::xml_attribute attribute_name = object_node.attribute("name"))
            object_name = attribute_name.as_string();
        // Check if the type attribute exists in object_node
        if (pugi::xml_attribute attribute_type = object_node.attribute("type"))
            object_type = attribute_type.as_string();
        // Check if the width and height attributes exists in object_node
        if (pugi::xml_attribute attribute_width = object_node.attribute("width"))
            object_width = attribute_width.as_uint();
        if (pugi::xml_attribute attribute_height = object_node.attribute("height"))
            object_height = attribute_height.as_uint();
        // Check if the type attribute exists in object_node
        if (pugi::xml_attribute attribute_rotation = object_node.attribute("rotation"))
            object_rotation = attribute_rotation.as_float();
        // Check if the type attribute exists in object_node
        if (pugi::xml_attribute attribute_visible = object_node.attribute("visible"))
            object_visible = attribute_visible.as_bool();

        if (object_width && object_height) {
            if (object_node.child("ellipse")) {
                // Ellipse Object
                tmx::Object newobject(object_name, object_type, object_x, object_y,
                                      object_width, object_height, object_rotation,
                                      object_visible, tmx::ObjectType::Ellipse);
                AddObjectProperties(object_node, &newobject);
                object_group->AddObject(newobject);
            } else {
                // Rectangle Object
                tmx::Object newobject(object_name, object_type, object_x, object_y,
                                      object_width, object_height, object_rotation,
                                      object_visible, tmx::ObjectType::Rectangle);
                AddObjectProperties(object_node, &newobject);
                object_group->AddObject(newobject);
            }
        } else {
            if (pugi::xml_node polygon_node = object_node.child("polygon")) {
                // Polygon Object
                std::string vertices_points = polygon_node.attribute("points").as_string();
                tmx::Object newobject(object_name, object_type, object_x, object_y,
                                      object_width, object_height, object_rotation,
                                      object_visible, tmx::ObjectType::Polygon, vertices_points);
                AddObjectProperties(object_node, &newobject);
                object_group->AddObject(newobject);
            } else if (pugi::xml_node polyline_node = object_node.child("polyline")) {
                // Polyline Object
                std::string vertices_points = polyline_node.attribute("points").as_string();
                tmx::Object newobject(object_name, object_type, object_x, object_y,
                                      object_width, object_height, object_rotation,
                                      object_visible, tmx::ObjectType::Polyline, vertices_points);
                AddObjectProperties(object_node, &newobject);
                object_group->AddObject(newobject);
            }
        }
    }

    return object_group;
}

}  // namespace tmx
