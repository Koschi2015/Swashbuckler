#include "StateManager.hpp"

StateManager::StateManager() :
    m_currentState(nullptr)
{ }

void StateManager::update(float frameTime)
{
    if(m_currentState)
        m_currentState->update(frameTime);
}

void StateManager::draw(const sf::RenderWindow& window)
{
    if(m_currentState)
        m_currentState->draw(window);
}

void StateManager::registerState(StateId id, std::unique_ptr<State> state)
{
    auto existingState = m_states.find(id);
    if(existingState != end(m_states))
        throw std::runtime_error("State is allready registered.");

    m_states[id] = std::move(state);
}