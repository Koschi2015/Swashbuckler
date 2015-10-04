#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include "../Map/World.hpp"

class ResourceManager;
class SpriteSheet;

class PlayState : public State
{
private:
    ResourceManager& m_resourceManager;
    sf::RenderWindow& m_window;

    sf::Sprite m_mouseIcon;
    SpriteSheet* m_mouseSpriteSheet;

    World m_world;
public:
    PlayState(Mouse& mouse,
              Keyboard& keyboard,
              ResourceManager& resourceManagaer,
              sf::RenderWindow& window);

    void update(float frameTime);

    void draw();

    void onEnter();

    void onLeave();
};

#endif