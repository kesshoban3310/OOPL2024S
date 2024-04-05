#ifndef APP_HPP
#define APP_HPP

#include "Core/Context.hpp"
#include "Util/Renderer.hpp"
#include "Component/Rockman.hpp"

class Phase;

class App {
public:
    enum class State {
        TITLE,
        MENU,
        STAGE,
        LOSE,
        ENDING_ANIMATION,
    };

    void ChangeState(State state);

    void Update();

    void SetCameraPosition(const glm::vec2 &position);

    void ResetCameraPosition();

    [[nodiscard]] State GetState() const;

    [[nodiscard]] std::shared_ptr<Util::Renderer> GetRoot() const;

    [[nodiscard]] std::shared_ptr<Core::Context> GetContext() const;

    [[nodiscard]] glm::vec2 GetCameraPosition() const;

    explicit App(State state);

    ~App();

private:
    std::unique_ptr<Phase> m_CurrentPhase;
    State m_CurrentState;
    std::shared_ptr<Util::Renderer> m_Root;
    std::shared_ptr<Core::Context> m_Context;
    glm::vec2 m_CameraPosition;
};

#endif // APP_HPP
