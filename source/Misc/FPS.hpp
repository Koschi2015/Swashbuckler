#ifndef FPS_HPP
#define FPS_HPP

namespace sf
{
    class RenderWindow;
    class Font;
}

class FPS
{
private:
    int m_lastFPS;
    int m_counterFPS;
    float m_nextFPSUpdate;

    sf::Font& m_font;
public:
    FPS(sf::Font& font);
    void update(float elapsedTime);
    void draw(sf::RenderWindow& window);
    int getFPS() const;
};

#endif