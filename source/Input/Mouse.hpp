#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "SFML\Window\Mouse.hpp"
#include <vector>

struct ButtonState
{
public:
    bool m_stillPressed;
    bool m_newlyPressed;
    bool m_released;
    bool m_isDown;

    ButtonState() :
        m_stillPressed(false),
        m_newlyPressed(false),
        m_released(false),
        m_isDown(false)
    { }
};

struct MouseButton
{
public:
    ButtonState m_state;
    sf::Mouse::Button m_button;

    MouseButton(const sf::Mouse::Button button) :
        m_button(button)
    { }
};

class Mouse
{
private:
    std::vector<MouseButton> m_buttons;
    bool m_mouseWheelDown;
    bool m_mouseWheelUp;

public:
    Mouse();
    virtual ~Mouse();

    void registerButton(const sf::Mouse::Button button);

    void capture();

    void notifyButtonPressed(const sf::Mouse::Button button);
    void notifyButtonReleased(const sf::Mouse::Button button);
    void notifyWheelMoved(const int delta);

    bool isWheelMovedUp() const;
    bool isWheelMovedDown() const;

    bool isButtonPressed(const sf::Mouse::Button button) const;
    bool isButtonReleased(const sf::Mouse::Button button) const;
    bool isButtonDown(const sf::Mouse::Button button) const;
};

#endif