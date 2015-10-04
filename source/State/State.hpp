#ifndef STATE_HPP
#define STATE_HPP

class Mouse;
class Keyboard;

enum StateId {None,
              PlayStateId};

class State
{
private:
    Mouse& m_mouse;
    Keyboard& m_keyboard;

protected:
    Mouse& getMouse() const;
    Keyboard& getKeyboard() const;

public:
    State(Mouse& mouse,
          Keyboard& keyboard);

    virtual ~State();

    virtual void update(float frameTime) = 0;

    virtual void draw() = 0;

    virtual void onEnter() = 0;

    virtual void onLeave() = 0;
};

#endif