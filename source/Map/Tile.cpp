#include "Tile.hpp"
#include "../Resources/SpriteSheet.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

Tile::Tile() :
    m_rep(""),
    m_name(""),
    m_textureIndex(nullptr),
    m_spriteSheet(nullptr),
    m_texture(nullptr)
{ }

Tile::Tile(const std::string& rep,
           const std::string& name,
           std::unique_ptr<Provider> textureIndex,
           const IsoPositionController& position) :
    m_rep(rep),
    m_name(name),
    m_textureIndex(std::move(textureIndex)),
    m_position(position),
    m_spriteSheet(nullptr),
    m_texture(nullptr)
{ }

Tile::Tile(const Tile& tile)
{
    m_rep = tile.m_rep;
    m_name = tile.m_name;
    if(tile.m_textureIndex == nullptr)
        m_textureIndex = nullptr;
    else
        m_textureIndex = std::move(tile.m_textureIndex->clone());
    m_position = tile.m_position;

    m_spriteSheet = tile.m_spriteSheet;
    m_texture = tile.m_texture;
}

Tile& Tile::operator= (const Tile& tile)
{
    m_rep = tile.m_rep;
    m_name = tile.m_name;
    if(tile.m_textureIndex == nullptr)
        m_textureIndex = nullptr;
    else
        m_textureIndex = std::move(tile.m_textureIndex->clone());
    m_position = tile.m_position;

    m_spriteSheet = tile.m_spriteSheet;
    m_texture = tile.m_texture;

    return *this;
}

const sf::Vector2i& Tile::getGridPosition() const
{
    return m_gridPosition;
}

void Tile::setGridPosition(const sf::Vector2i& position)
{
    m_gridPosition = IsoPositionController(position.x, position.y);
    m_position.x = position.x * 16.f- position.y * 16.f;
    m_position.y = position.y * 8.f + position.x * 8.f;
    m_sprite.setPosition(m_position);
}

void Tile::update(float elapsedTime)
{
    m_textureIndex->update(elapsedTime);
    
    m_sprite.setTexture(*m_texture);
    m_sprite.setTextureRect(m_spriteSheet->getTextureRect(static_cast<int>(m_textureIndex->getValue())));
    m_sprite.setPosition(m_position);
}

void Tile::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Tile::bindSpriteSheet(SpriteSheet& spriteSheet)
{
    m_spriteSheet = &spriteSheet;
}

void Tile::bindTexture(sf::Texture* texture)
{
    m_texture = texture;
    m_sprite.setTexture(*m_texture);
    m_sprite.setTextureRect(m_spriteSheet->getTextureRect(static_cast<int>(m_textureIndex->getValue())));
}