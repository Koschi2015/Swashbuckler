#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"

class Mouse;
class Keyboard;

class ResourceManager;

namespace sf
{
    class RenderWindow;
}

class World
{
private:
    Mouse& m_mouse;
    Keyboard& m_keyboard;

    sf::RenderWindow& m_window;

    Map m_currentMap;
    sf::Vector2f m_playerPosition;

    ResourceManager& m_resourceManager;

public:
    World(ResourceManager& resourceManager, Mouse& mouse, Keyboard& keyboard, sf::RenderWindow& window);

    void update(float elapsedTime);

    void draw();
};

#endif