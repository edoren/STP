#include <cassert>
#include <cmath>
#include "STP/Core/TileSet.hpp"
#include <iostream>

namespace TMX {

TileSet::TileSet(unsigned int firstgid, const std::string& name, unsigned int tilewidth, 
        unsigned int tileheight, unsigned int spacing, unsigned int margin,
        TMX::TileSet::image image, TMX::TileSet::tileoffset tileoffset) :
m_firstgid(firstgid),
m_name(name),
m_tilewidth(tilewidth),
m_tileheight(tileheight),
m_spacing(spacing),
m_margin(margin),
m_image(image),
m_tileoffset(tileoffset)
{
    m_lastgid = m_firstgid + (m_image.width / m_tilewidth) * (m_image.height / m_tileheight) - 1;
    m_texture.loadFromFile(m_image.source);
}

TileSet::~TileSet()
{

}

// Struct default constructors
TileSet::tileoffset::tileoffset() :
x(0),
y(0)
{
}

TileSet::image::image() :
format(0)
{
}

sf::IntRect TileSet::getTextureRect(unsigned int gid) {
    assert(gid >= m_firstgid && gid <= m_lastgid);
    int local_gid, width, height, x, y, x_pixels, y_pixels;
    local_gid = gid - m_firstgid + 1;
    width = m_image.width / m_tilewidth;
    height = m_image.height / m_tileheight;
    y = static_cast<int> (std::ceil(local_gid / static_cast<float>(width)));
    x = local_gid - ((y - 1) * width);
    y_pixels = (y - 1) * m_tilewidth;
    x_pixels = (x - 1) * m_tileheight;
    sf::IntRect tilerect(x_pixels, y_pixels, m_tilewidth, m_tileheight);
    return tilerect;
}

const sf::Texture* TileSet::getTexture() {
    return &m_texture;
}

unsigned int TileSet::getFirstGID() {
    return m_firstgid;
}

unsigned int TileSet::getLastGID() {
    return m_lastgid;
}

}
