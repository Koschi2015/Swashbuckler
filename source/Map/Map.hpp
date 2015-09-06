#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "Tile.hpp"

class ResourceManager;
namespace sf
{
    class RenderWindow;
}

class Map
{
private:
    std::vector<Tile> m_Tiles;
    ResourceManager& m_resourceManager;

public:
    Map(ResourceManager& m_resourceManager);

    void update(float frameTime);

    void draw(sf::RenderWindow& window);

    void load(const std::string& mapKey);
};

#endif