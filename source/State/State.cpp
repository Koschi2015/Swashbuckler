#include "State.hpp"
#include "../Input/Mouse.hpp"
#include "../Input/Keyboard.hpp"

State::State(Mouse& mouse,
             Keyboard& keyboard) :
    m_mouse(mouse),
    m_keyboard(keyboard)
{ }

State::~State()
{ }

Mouse& State::getMouse() const
{
    return m_mouse;
}

Keyboard& State::getKeyboard() const
{
    return m_keyboard;
}