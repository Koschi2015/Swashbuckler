#include "World.hpp"
#include "../Input/Mouse.hpp"
#include "../Input/Keyboard.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

World::World(ResourceManager& resourceManager, Mouse& mouse, Keyboard& keyboard, sf::RenderWindow& window) :
    m_resourceManager(resourceManager),
    m_currentMap(resourceManager),
    m_mouse(mouse),
    m_keyboard(keyboard),
    m_window(window)
{
    m_currentMap.load("test");
}

void World::update(float elapsedTime)
{
    m_currentMap.update(elapsedTime);
}

void World::draw()
{
    m_currentMap.draw(m_window);
}