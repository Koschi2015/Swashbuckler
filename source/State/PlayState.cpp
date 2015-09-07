#include "PlayState.hpp"
#include "../Input/Keyboard.hpp"
#include "../Input/Mouse.hpp"
#include "../Resources/ResourceManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

PlayState::PlayState(Mouse& mouse,
                     Keyboard& keyboard,
                     ResourceManager& resourceManager,
                     sf::RenderWindow& window) :
    State(mouse, keyboard),
    m_resourceManager(resourceManager),
    m_window(window),
    m_mouseSpriteSheet(nullptr)
{
    m_mouseIcon.setTexture(*m_resourceManager.getTexture("mouse"));
    m_mouseSpriteSheet = m_resourceManager.getSpriteSheet("mouse");
    m_mouseIcon.setTextureRect(m_mouseSpriteSheet->getTextureRect("arrow"));
    m_mouseIcon.setPosition(State::getMouse().getLocalPosition(m_window));
}

void PlayState::update(float frameTime)
{
    m_mouseIcon.setPosition(State::getMouse().getLocalPosition(m_window));
}

void PlayState::draw(sf::RenderWindow& window)
{
    window.draw(m_mouseIcon);
}

void PlayState::onEnter()
{
    State::getMouse().hideSystemCursor(m_window);
}

void PlayState::onLeave()
{
    State::getMouse().showSystemCursor(m_window);
}