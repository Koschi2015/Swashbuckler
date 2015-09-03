#ifndef APP_HPP
#define APP_HPP

#include "Input/Mouse.hpp"
#include "Input/Keyboard.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class App
{
private:
    void update();
    void draw();

    sf::RenderWindow m_window;

    Mouse m_mouse;
    Keyboard m_keyboard;

    bool m_quit;

public:
    App();

    void run();
};

#endif