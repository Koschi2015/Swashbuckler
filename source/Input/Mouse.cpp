#include "Mouse.hpp"
#include <SFML\Graphics\RenderWindow.hpp>
#include <stdexcept>

Mouse::Mouse()
{ }

Mouse::~Mouse()
{ }

void Mouse::registerButton(const sf::Mouse::Button button)
{
    for(auto it = begin(m_buttons); it != end(m_buttons); ++it)
    {
        if(it->m_button == button)
            std::runtime_error("Mousebutton alredy registered.");
    }

    MouseButton newButton(button);
    m_buttons.push_back(newButton);
}

void Mouse::capture()
{
    for(auto it = begin(m_buttons); it != end(m_buttons); ++it)
    {
        it->m_state.m_newlyPressed = it->m_state.m_isDown && !it->m_state.m_stillPressed;
        bool last = it->m_state.m_stillPressed;
        it->m_state.m_stillPressed = it->m_state.m_isDown;
        it->m_state.m_released = last && !it->m_state.m_stillPressed;
    }

    m_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition());

    m_mouseWheelDown = false;
    m_mouseWheelUp = false;
}

void Mouse::notifyButtonPressed(const sf::Mouse::Button button)
{
    for(auto it = begin(m_buttons); it != end(m_buttons); ++it)
    {
        if(it->m_button == button)
        {
            it->m_state.m_isDown = true;
            return;
        }
    }
}

void Mouse::notifyButtonReleased(const sf::Mouse::Button button)
{
    for(auto it = begin(m_buttons); it != end(m_buttons); ++it)
    {
        if(it->m_button == button)
        {
            it->m_state.m_isDown = false;
            return;
        }
    }
}

void Mouse::notifyWheelMoved(const int delta)
{
    if(delta > 0)
    {
        m_mouseWheelUp = true;
        m_mouseWheelDown = false;
    }
    else if(delta < 0)
    {
        m_mouseWheelDown = true;
        m_mouseWheelUp = false;
    }
}

bool Mouse::isButtonPressed(const sf::Mouse::Button button) const
{
    for(auto it = begin(m_buttons); it != end(m_buttons); ++it)
    {
        if(it->m_button == button)
            return it->m_state.m_stillPressed;
    }

    return false;
}
bool Mouse::isButtonReleased(const sf::Mouse::Button button) const
{
    for(auto it = begin(m_buttons); it != end(m_buttons); ++it)
    {
        if(it->m_button == button)
            return it->m_state.m_released;
    }

    return false;
}
bool Mouse::isButtonDown(const sf::Mouse::Button button) const
{
    for(auto it = begin(m_buttons); it != end(m_buttons); ++it)
    {
        if(it->m_button == button)
            return it->m_state.m_newlyPressed;
    }

    return false;
}

bool Mouse::isWheelMovedUp() const
{
    return m_mouseWheelUp;
}

bool Mouse::isWheelMovedDown() const
{
    return m_mouseWheelDown;
}

const sf::Vector2f& Mouse::getGlobalPosition() const
{
    return m_position;
}

sf::Vector2f Mouse::getLocalPosition(const sf::RenderWindow& relativTo) const
{
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(relativTo));
}

void Mouse::hideSystemCursor(sf::RenderWindow& window)
{
    window.setMouseCursorVisible(false);
    m_cursorVisible = false;
}

void Mouse::showSystemCursor(sf::RenderWindow& window)
{
    window.setMouseCursorVisible(true);
    m_cursorVisible = true;
}

bool Mouse::isSystemCursorVisible() const
{
    return m_cursorVisible;
}