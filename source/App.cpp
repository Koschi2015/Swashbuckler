#include "App.hpp"

App::App() :
    m_quit(false)
{
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
}

void App::update()
{
}