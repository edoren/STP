#include "STP/Core/Layer.hpp"

namespace TMX {

Layer::Layer(const std::string& name, unsigned int width, unsigned int height, float opacity, bool visible) :
m_name(name),
m_width(width),
m_height(height),
m_opacity(opacity),
visible(visible)
{
    // Reserve space for each vector to avoid reallocate
    m_tiles.reserve(m_height);
    for (int i = 0; i < m_height; i++) {
        std::vector<TMX::Tile> newvec;
        newvec.reserve(m_width);
        m_tiles.push_back(newvec);
    }
};

Layer::~Layer()
{

}

int Layer::addTile(TMX::Tile newtile) {
    for (int i = 0; i < m_height; i++) {  
        if(m_tiles[i].size() < m_width) {
            m_tiles[i].push_back(newtile);
            return 0;
        }
    }
    return -1;
}

void Layer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int y = 0; y < m_tiles.size(); y++) {
        for (int x = 0; x < m_tiles[y].size(); x++) {
            target.draw(m_tiles[y][x]);
        }
    }
}

}
