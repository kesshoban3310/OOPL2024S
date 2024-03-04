#ifndef APP_HPP
#define APP_HPP

#include "ImageObject.hpp"
#include "Util/GameObject.hpp"
#include "Util/Root.hpp"
#include "pch.hpp" // IWYU pragma: export

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
    State m_CurrentState = State::START;
    Util::Root m_Root;

    // game objects
    std::shared_ptr<ImageObject> background;
};

#endif
