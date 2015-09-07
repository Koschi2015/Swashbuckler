#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "Tile.hpp"

class ResourceManager;
class SpriteSheet;
namespace sf
{
    class RenderWindow;
    class Texture;
}

class Map
{
private:
    std::vector<Tile> m_Tiles;
    ResourceManager& m_resourceManager;
    SpriteSheet* m_currentMapSheet;
    sf::Texture* m_currentTexture;

public:
    Map(ResourceManager& m_resourceManager);

    void update(float frameTime);

    void draw(sf::RenderWindow& window);

    void load(const std::string& mapKey);
};

#endif