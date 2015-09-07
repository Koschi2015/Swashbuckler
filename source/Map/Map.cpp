#include "Map.hpp"
#include "../Resources/ResourceManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Map::Map(ResourceManager& resourceManager) :
    m_resourceManager(resourceManager),
    m_currentMapSheet(nullptr),
    m_currentTexture(nullptr)
{ }

void Map::update(float frameTime)
{
}

void Map::draw(sf::RenderWindow& window)
{
}

void Map::load(const std::string& mapKey)
{
}