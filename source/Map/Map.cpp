#include "Map.hpp"
#include "../Resources/ResourceManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Map::Map(ResourceManager& resourceManager) :
    m_resourceManager(resourceManager),
    m_currentMapSheet(nullptr),
    m_currentTexture(nullptr)
{ }

void Map::update(float elapsedTime)
{
    for(auto it = begin(m_tiles); it != end(m_tiles); ++it)
    {
        for(auto jt = begin(*it); jt != end(*it); ++jt)
            jt->update(elapsedTime);
    }
        
}

void Map::draw(sf::RenderWindow& window)
{
    for(auto it = begin(m_tiles); it != end(m_tiles); ++it)
    {
        for(auto jt = begin(*it); jt != end(*it); ++jt)
        {
            jt->draw(window);
        }
    }
}