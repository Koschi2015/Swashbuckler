#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics/Sprite.hpp>

class ResourceManager;

class PlayState : public State
{
private:
    const ResourceManager& m_resourceManager;
    sf::RenderWindow& m_window;

    sf::Sprite m_mouseIcon;
public:
    PlayState(Mouse& mouse,
              Keyboard& keyboard,
              const ResourceManager& resourceManagaer,
              sf::RenderWindow& window);

    void update(float frameTime);

    void draw(sf::RenderWindow& window);

    void onEnter();

    void onLeave();
};

#endif