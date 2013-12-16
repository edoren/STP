#include "STP/Core/Tile.hpp"
#include <iostream>

namespace TMX {

Tile::Tile()
{

}

Tile::Tile(unsigned int gid, sf::IntRect tile_rect,
           const sf::Texture* texture, sf::IntRect texture_rect) :
m_gid(gid),
m_tile_rect(tile_rect),
m_texture(texture),
m_texture_rect(texture_rect),
m_vertices(sf::Quads, 4)
{
    m_vertices[0].position = sf::Vector2f(m_tile_rect.left, m_tile_rect.top);
    m_vertices[1].position = sf::Vector2f(m_tile_rect.left + m_tile_rect.width, m_tile_rect.top);
    m_vertices[2].position = sf::Vector2f(m_tile_rect.left + m_tile_rect.width, m_tile_rect.top + m_tile_rect.height);
    m_vertices[3].position = sf::Vector2f(m_tile_rect.left, m_tile_rect.top + m_tile_rect.height);

    if(texture != NULL) {
        m_vertices[0].texCoords = sf::Vector2f(m_texture_rect.left, m_texture_rect.top);
        m_vertices[1].texCoords = sf::Vector2f(m_texture_rect.left + m_texture_rect.width, m_texture_rect.top);
        m_vertices[2].texCoords = sf::Vector2f(m_texture_rect.left + m_texture_rect.width, m_texture_rect.top + m_texture_rect.height);
        m_vertices[3].texCoords = sf::Vector2f(m_texture_rect.left, m_texture_rect.top + m_texture_rect.height);
    }
};

Tile::~Tile()
{

}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_texture != NULL) {
        // apply the texture
        states.texture = m_texture;
        // draw the vertex array
        target.draw(m_vertices, states);
    }
}

}
