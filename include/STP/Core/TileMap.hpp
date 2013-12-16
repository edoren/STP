#ifndef STP_TILEMAP_HPP
#define STP_TILEMAP_HPP

#include "STP/Core/TileSet.hpp"
#include "STP/Core/Layer.hpp"
#include <vector>

namespace TMX {

class TileMap : public sf::Drawable {
public:
    TileMap(float _version, const std::string& _orientation, unsigned int _width, unsigned int _height, unsigned int _tilewidth, unsigned int _tileheight);
    ~TileMap();

    void addLayer(TMX::Layer newlayer);
    void addTileSet(TMX::TileSet newtileset);

    // Return the tileset attached to the global id
    TMX::TileSet* getTileSet(unsigned int gid);
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<TMX::Layer> m_layers;
private:
    float m_version;
    std::string m_orientation;
    unsigned int m_width, m_height, m_tilewidth, m_tileheight;

    std::vector<TMX::TileSet> m_tilesets;
};

}

#endif // STP_TILEMAP_HPP
