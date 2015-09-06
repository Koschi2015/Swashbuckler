#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/System/Vector2.hpp>

class Tile
{
private:
    sf::Vector2i m_position;
    int m_textureIndex;

public:
    Tile(const sf::Vector2i& position, int textureIndex);

    sf::Vector2i getPosition() const;
    int getTextureIndex() const;
};

#endif