#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SFML/Window/Keyboard.hpp>
#include <vector>

class Keyboard
{
public:
    Keyboard()
    { }

    void progress();

    void notifyKeyPressed(const sf::Keyboard::Key key);

    void notifyKeyReleased(const sf::Keyboard::Key key);

    bool isKeyDown(const sf::Keyboard::Key key);

    bool isKeyPressed(const sf::Keyboard::Key key);

    bool isKeyReleased(const sf::Keyboard::Key key);

private:
    std::vector<sf::Keyboard::Key> m_newlyPressed;
    std::vector<sf::Keyboard::Key> m_stillPressed;
    std::vector<sf::Keyboard::Key> m_released;
};

#endif
