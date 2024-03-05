#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "BackGround.hpp"
#include "Util/Root.hpp"


class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    Util::Root m_Root;
    State m_CurrentState = State::START;
    std::shared_ptr<BackGround> m_BackGround;
};

#endif
