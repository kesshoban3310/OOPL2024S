#ifndef APP_HPP
#define APP_HPP

#include "BackGroundImage.hpp"
#include "Util/Root.hpp"
#include "pch.hpp" // IWYU pragma: export
#include "BackGroundMap.hpp"


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
    std::shared_ptr<BackGroundImage> m_BackGround;
    std::shared_ptr<BackGroundMap> m_Map;
};

#endif
