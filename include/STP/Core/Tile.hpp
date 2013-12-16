#ifndef STP_TILE_HPP
#define STP_TILE_HPP

#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace TMX {

class Tile : public sf::Drawable {
public:
    Tile();
    Tile(unsigned int gid, sf::IntRect tile_rect, 
         const sf::Texture* texture, sf::IntRect texture_rect = sf::IntRect(0,0,0,0));
    ~Tile();

private:
    unsigned int m_gid;

    sf::IntRect m_tile_rect;
    sf::VertexArray m_vertices;

    const sf::Texture* m_texture;
    sf::IntRect m_texture_rect;

    void setTexture(unsigned int gid);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

#endif // STP_TILE_HPP
