#ifndef APP_HPP
#define APP_HPP

#include "Input/Mouse.hpp"
#include "Input/Keyboard.hpp"
#include "State/StateManager.hpp"
#include "Resources/ResourceManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class App
{
private:
    void update();
    void draw();

    sf::RenderWindow m_window;
    
    sf::Clock m_frameTime;

    Mouse m_mouse;
    Keyboard m_keyboard;

    StateManager m_stateManager;
    ResourceManager m_resourceManager;

    bool m_quit;

public:
    App();

    void run();
};

#endif