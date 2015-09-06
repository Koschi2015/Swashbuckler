#include "Tile.hpp"

Tile::Tile(const sf::Vector2i& position, int textureIndex) :
    m_position(position),
    m_textureIndex(textureIndex)
{ }

sf::Vector2i Tile::getPosition() const
{
    return m_position;
}

int Tile::getTextureIndex() const
{
    return m_textureIndex;
}