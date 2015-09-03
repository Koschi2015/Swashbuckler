#include "Keyboard.hpp"
#include <algorithm>

void Keyboard::progress()
{
    m_released.clear();
    m_newlyPressed.clear();
}

void Keyboard::notifyKeyPressed(const sf::Keyboard::Key key)
{
    if(std::find(begin(m_stillPressed), end(m_stillPressed), key) == end(m_stillPressed))
    {
        m_newlyPressed.push_back(key);
        m_stillPressed.push_back(key);
    }
}

void Keyboard::notifyKeyReleased(const sf::Keyboard::Key key)
{
    auto it = std::find(begin(m_stillPressed), end(m_stillPressed), key);
    if(it != end(m_stillPressed))
        m_stillPressed.erase(it);
    m_released.push_back(key);
}

bool Keyboard::isKeyDown(const sf::Keyboard::Key key)
{
    return std::find(begin(m_newlyPressed), end(m_newlyPressed), key) != end(m_newlyPressed);
}

bool Keyboard::isKeyPressed(const sf::Keyboard::Key key)
{
    return std::find(begin(m_stillPressed), end(m_stillPressed), key) != end(m_stillPressed);
}

bool Keyboard::isKeyReleased(const sf::Keyboard::Key key)
{
    return std::find(begin(m_released), end(m_released), key) != end(m_released);
}