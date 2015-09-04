#ifndef STATE_HPP
#define STATE_HPP

class Mouse;
class Keyboard;

namespace sf
{
    class RenderWindow;
}

class State
{
private:
    const Mouse& m_mouse;
    const Keyboard& m_keyboard;

protected:
    const Mouse& getMouse() const;
    const Keyboard& getKeyboard() const;

public:
    State(const Mouse& mouse,
          const Keyboard& keyboard);

    virtual ~State();

    virtual void update(float frameTime) = 0;

    virtual void draw(const sf::RenderWindow& window) = 0;
};

#endif