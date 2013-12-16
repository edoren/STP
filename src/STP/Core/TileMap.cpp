#include "STP/Core/TileMap.hpp"

namespace TMX {

TileMap::TileMap(float version, const std::string& orientation, unsigned int width,
                 unsigned int height, unsigned int tilewidth, unsigned int tileheight) :
m_version    (version),
m_orientation(orientation),
m_width      (width),
m_height     (height),
m_tilewidth  (tilewidth),
m_tileheight (tileheight)
{
    
}

TileMap::~TileMap()
{

}

void TileMap::addLayer(TMX::Layer newlayer) {
    m_layers.push_back(newlayer);
}

void TileMap::addTileSet(TMX::TileSet newtileset) {
    m_tilesets.push_back(newtileset);
}

TMX::TileSet* TileMap::getTileSet(unsigned int gid) {
    if(gid == 0) return NULL;
    for (int i = 0; i < m_tilesets.size(); ++i) {
        if(gid >= m_tilesets[i].getFirstGID() && gid <= m_tilesets[i].getLastGID())
            return &m_tilesets[i];
    }
    return NULL;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < m_layers.size(); i++) {
        if(m_layers[i].visible == true)
            target.draw(m_layers[i]);
    }
}

}
