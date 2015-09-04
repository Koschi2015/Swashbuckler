#include "State.hpp"
#include "../Input/Mouse.hpp"
#include "../Input/Keyboard.hpp"

State::State(const Mouse& mouse,
             const Keyboard& keyboard) :
    m_mouse(mouse),
    m_keyboard(keyboard)
{ }

State::~State()
{ }

const Mouse& State::getMouse() const
{
    return m_mouse;
}

const Keyboard& State::getKeyboard() const
{
    return m_keyboard;
}