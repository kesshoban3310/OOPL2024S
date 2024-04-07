#include "Component/Phase.hpp"

Phase::Phase(App::State lastState)
    : m_LastState(lastState) {}

App::State Phase::GetLastState() const {
    return m_LastState;
}
