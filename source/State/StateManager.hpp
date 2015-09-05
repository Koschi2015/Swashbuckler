#ifndef STATEMANAGER_HPP
#define STATEMANAGER_HPP

#include "State.hpp"
#include <map>

enum StateId {None,
              PlayStateId};

class StateManager
{
private:
    State* m_currentState;
    StateId m_currentStateId;

    std::map<StateId, std::unique_ptr<State>> m_states;

    float m_lastFrameTime;
    float m_pauseDelayTime;

    bool m_paused;
public:
    StateManager();

    void update(float frameTime);
    void draw(const sf::RenderWindow& window);

    void registerState(StateId id, std::unique_ptr<State> state);
};

#endif