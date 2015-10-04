#include "App.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "State/PlayState.hpp"


App::App() :
    m_window(sf::VideoMode(800, 600), "Swashbuckler"),
    m_resourceManager("resources/resources.nfo"),
    m_quit(false),
    m_fpsCounter(*m_resourceManager.getFont("modernefraktur"))
{
    m_mouse.registerButton(sf::Mouse::Left);

    m_frameTime.restart();
    m_stateManager.registerState(PlayStateId, std::unique_ptr<PlayState>(new PlayState(m_mouse, m_keyboard, m_resourceManager, m_window)));
    m_stateManager.setState(PlayStateId);
}

void App::run()
{
    while(!m_quit)
    {
        update();
        draw();
    }
}

void App::draw()
{
    m_window.clear();
    m_stateManager.draw();
    m_fpsCounter.draw(m_window);
    m_window.display();
}

void App::update()
{
    m_mouse.capture();
    m_keyboard.progress();

    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(sf::Event::Closed == event.type)
            m_quit = true;

        if(sf::Event::MouseButtonPressed == event.type)
            m_mouse.notifyButtonPressed(event.mouseButton.button);

        if(sf::Event::MouseButtonReleased == event.type)
            m_mouse.notifyButtonReleased(event.mouseButton.button);

        if(sf::Event::MouseWheelMoved == event.type)
            m_mouse.notifyWheelMoved(event.mouseWheel.delta);

        if(sf::Event::KeyPressed == event.type)
            m_keyboard.notifyKeyPressed(event.key.code);

        if(sf::Event::KeyReleased == event.type)
            m_keyboard.notifyKeyReleased(event.key.code);
    }
    m_fpsCounter.update(m_frameTime.getElapsedTime().asSeconds());
    m_stateManager.update(m_frameTime.getElapsedTime().asSeconds());
}
