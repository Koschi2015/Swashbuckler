#include "StateManager.hpp"

StateManager::StateManager() :
    m_currentState(nullptr),
    m_lastFrameTime(0),
    m_pauseDelayTime(0),
    m_paused(false)
{ }

void StateManager::update(float frameTime)
{
    if(m_paused)
    {
        float delta = frameTime - m_lastFrameTime;
        m_pauseDelayTime += delta;
    }

    if(m_currentState && !m_paused)
        m_currentState->update(frameTime - m_pauseDelayTime);

    m_lastFrameTime = frameTime;
}

void StateManager::draw()
{
    if(m_currentState && !m_paused)
        m_currentState->draw();
}

void StateManager::registerState(StateId id, std::unique_ptr<State> state)
{
    auto existingState = m_states.find(id);
    if(existingState != end(m_states))
        throw std::runtime_error("State is allready registered.");

    m_states[id] = std::move(state);
}

void StateManager::setState(StateId id)
{
    auto state = m_states.find(id);
    if(state == end(m_states))
        throw std::runtime_error("State is not registered.");

    if(m_currentState)
        m_currentState->onLeave();

    m_currentState = state->second.get();
    m_currentStateId = id;

    m_currentState->onEnter();
}