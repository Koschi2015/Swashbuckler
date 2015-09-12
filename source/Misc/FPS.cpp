#include "FPS.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Utility.hpp"

FPS::FPS(sf::Font& font):
    m_lastFPS(0),
    m_counterFPS(0),
    m_nextFPSUpdate(0),
    m_font(font)
{ }

void FPS::update(float elapsedTime)
{
    if(m_nextFPSUpdate < elapsedTime)
    {
        m_lastFPS = m_counterFPS + 1;
        m_nextFPSUpdate = elapsedTime +1.f;
        m_counterFPS = 0;
    }
    else
        ++m_counterFPS;
}

int FPS::getFPS() const
{
    return m_lastFPS;
}

void FPS::draw(sf::RenderWindow& window)
{
    sf::Text fps;
    fps.setString(utility::toString(m_lastFPS));
    fps.setFont(m_font);
    window.draw(fps);
}