#ifndef TILE_HPP
#define TILE_HPP

#include <memory>
#include <string>
#include "IsoPositionController.hpp"
#include "../Provider/Provider.hpp"
#include <SFML/Graphics/Sprite.hpp>

class SpriteSheet;
namespace sf
{
    class RenderWindow;
    class Texture;
}

class Tile
{
private:
    std::string m_rep;
    std::string m_name;
    std::unique_ptr<Provider> m_textureIndex;
    IsoPositionController m_gridPosition;
    sf::Vector2f m_position;
    sf::Sprite m_sprite;
    SpriteSheet* m_spriteSheet;
    sf::Texture* m_texture;
public:
    Tile();
    Tile(const std::string& rep,
         const std::string& name,
         std::unique_ptr<Provider> textureIndex,
         const IsoPositionController& position = IsoPositionController(0, 0));
    Tile(const Tile& tile);
    
    Tile& operator= (const Tile& tile);
    
    void update(float elapsedTime);
    void draw(sf::RenderWindow& window);

    const sf::Vector2i& getGridPosition() const;

    void setGridPosition(const sf::Vector2i& position);

    void bindSpriteSheet(SpriteSheet& spriteSheet);
    void bindTexture(sf::Texture* texture);
};

#endif