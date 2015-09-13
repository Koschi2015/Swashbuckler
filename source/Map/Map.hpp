#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <unordered_map>
#include "Tile.hpp"

class ResourceManager;
class SpriteSheet;

namespace sf
{
    class RenderWindow;
    class Texture;
}

namespace tinyxml2
{
    class XMLDocument;
}

typedef std::unordered_map<std::string, Tile> TilePool;
typedef std::unordered_map<std::string, std::unique_ptr<Provider>> ProviderPool;

class Map
{
    // Map_LoadingPart - Function
private:
    void parseTile(tinyxml2::XMLDocument& doc,
                   TilePool& tilePool,
                   ProviderPool& providerPool);

    void parseProvider(tinyxml2::XMLDocument& doc,
                       ProviderPool& providerPool);

    void parseGrid(tinyxml2::XMLDocument& doc,
                   TilePool& tilePool);

    void parseTextureData(tinyxml2::XMLDocument& doc);
private:
    std::vector<Tile> m_tiles;
    sf::Vector2u m_tileSize;
    ResourceManager& m_resourceManager;
    SpriteSheet* m_currentMapSheet;
    sf::Texture* m_currentTexture;

public:
    Map(ResourceManager& m_resourceManager);

    void update(float elapsedTime);

    void draw(sf::RenderWindow& window);

    void load(const std::string& mapKey);
};

#endif