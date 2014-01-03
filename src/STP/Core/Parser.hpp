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

#ifndef STP_PARSER_HPP
#define STP_PARSER_HPP

#include <vector>
#include <string>

#include "pugixml.hpp"

#include "STP/Config.hpp"
#include "STP/Core/Properties.hpp"
#include "STP/Core/TileMap.hpp"
#include "STP/Core/TileSet.hpp"
#include "STP/Core/Layer.hpp"
#include "STP/Core/ObjectGroup.hpp"
#include "STP/Core/ImageLayer.hpp"

namespace tmx {

tmx::TileSet* ParseTileSet(pugi::xml_node& tileset_node, const std::string& working_dir);
tmx::Layer* ParseLayer(pugi::xml_node& layer_node, const tmx::TileMap* tilemap);
tmx::ObjectGroup* ParseObjectGroup(pugi::xml_node& object_group_node);
tmx::ImageLayer* ParseImageLayer(pugi::xml_node& imagelayer_node, const std::string& working_dir);
void ParseProperties(pugi::xml_node& object_node, tmx::Properties* object);

}  // namespace tmx

#endif  // STP_PARSER_HPP
