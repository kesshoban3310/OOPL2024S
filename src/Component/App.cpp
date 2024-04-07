#include "Component/App.hpp"
#include "PhaseEndingAnimation.hpp"
#include "PhaseLose.hpp"
#include "PhaseMenu.hpp"
#include "PhaseStage.hpp"
#include "PhaseTitle.hpp"
#include "Util/Input.hpp"

void App::ChangeState(State state) {
    // reset the camera position
    ResetCameraPosition();

    // remove all children from the root
    m_Root->RemoveAllChildren();

    // leave the old state
    if (m_CurrentPhase)
        m_CurrentPhase->Leave(this);

    // create the new state
    switch (state) {
    case State::TITLE:
        m_CurrentPhase = std::make_unique<PhaseTitle>(m_CurrentState);
        break;

    case State::MENU:
        m_CurrentPhase = std::make_unique<PhaseMenu>(m_CurrentState);
        break;

    case State::STAGE:
        m_CurrentPhase = std::make_unique<PhaseStage>(m_CurrentState);
        break;

    case State::LOSE:
        m_CurrentPhase = std::make_unique<PhaseLose>(m_CurrentState);
        break;

    case State::ENDING_ANIMATION:
        m_CurrentPhase = std::make_unique<PhaseEndingAnimation>(m_CurrentState);
        break;
    }
    m_CurrentState = state;

    // initialize the new state
    if (m_CurrentPhase)
        m_CurrentPhase->Init(this);
}

void App::Update() {
    // update the current state
    if (m_CurrentPhase)
        m_CurrentPhase->Update(this);

    // render the root at the camera position
    m_Root->Update(-m_CameraPosition);

    // update the context
    m_Context->Update();

    // if pressed ESC, exit the app
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE)) {
        m_Context->SetExit(true);
    }
}

void App::SetCameraPosition(const glm::vec2 &position) {
    m_CameraPosition = position;
}

void App::ResetCameraPosition() {
    m_CameraPosition = {0, 0};
}

App::State App::GetState() const {
    // get the current state
    return m_CurrentState;
}

std::shared_ptr<Util::Renderer> App::GetRoot() const {
    return m_Root;
}

glm::vec2 App::GetCameraPosition() const {
    return m_CameraPosition;
}

App::App(State state)
    : m_CurrentPhase(nullptr),
      m_CurrentState(state),
      m_Root(std::make_shared<Util::Renderer>()),
      m_Context(Core::Context::GetInstance()),
      m_CameraPosition({0, 0}) {
    ChangeState(state);
}

App::~App() {
    // leave the current state
    if (m_CurrentPhase)
        m_CurrentPhase->Leave(this);
}

std::shared_ptr<Core::Context> App::GetContext() const {
    return m_Context;
}
