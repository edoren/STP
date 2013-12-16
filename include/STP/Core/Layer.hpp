#ifndef STP_LAYER_HPP
#define STP_LAYER_HPP

#include <string>
#include <vector>
#include "STP/Core/Tile.hpp"

namespace TMX {

class Layer : public sf::Drawable {
public:
    Layer(const std::string& _name, unsigned int _width, 
          unsigned int _height, float _opacity, bool _visible);
    ~Layer();

    int addTile(TMX::Tile newtile);

    bool visible;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    std::string m_name;
    unsigned int m_width, m_height;
    float m_opacity; //range 0 - 1

    std::vector< std::vector<TMX::Tile> > m_tiles;
};

}

#endif // STP_LAYER_HPP
