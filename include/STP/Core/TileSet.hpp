#ifndef STP_TILESET_HPP
#define STP_TILESET_HPP

#include <string>
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace TMX {

class TileSet {
public:
    struct tileoffset { // 0.2
        int x, y;
        tileoffset();
    };

    struct image {
        int format;
        std::string source, trans; // trans 0.2
        unsigned int width, height;
        image();
    };

    struct terraintypes { // 0.2
    };

    struct layer { // 0.2
    };

public:
    TileSet(unsigned int firstgid, const std::string& name, unsigned int tilewidth,
            unsigned int tileheight, unsigned int spacing, unsigned int margin,
            TMX::TileSet::image image, TMX::TileSet::tileoffset tileoffset);

    ~TileSet();

    sf::IntRect getTextureRect(unsigned int gid);
    const sf::Texture* getTexture();

    unsigned int getFirstGID();
    unsigned int getLastGID();

private:
    unsigned int m_firstgid, m_lastgid, m_tilewidth, m_tileheight, m_spacing, m_margin; // spacing, margin - 0.2

    std::string m_name;
    struct TMX::TileSet::image m_image;
    struct TMX::TileSet::tileoffset m_tileoffset;
    sf::Texture m_texture;
};

}

#endif // STP_TILESET_HPP
