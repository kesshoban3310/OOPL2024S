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

    // if pressed ESC or exit button, exit the app
    if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
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
    m_WordDebug = std::make_shared<Words>("debug mode on",glm::vec2 {2,2});
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

void App::SetLifeCount(unsigned int count) {
    m_LifeCount = count;
}

unsigned int App::GetLifeCount() const {
    return m_LifeCount;
}
void App::SetDebugModeState(bool debugstate) {
    m_DebugMode = debugstate;
}
bool App::GetDebugModeState() const {
    return m_DebugMode;
}
std::shared_ptr<Words> App::GetDebugModeWords() const{
    return m_WordDebug;
}
void App::SetDebugModeMessagePosition(const glm::vec2 &position){
    int Xscale = 0,Yscale = 0;
    glm::vec2 WordInitialPosition = {position.x+188,position.y+308};
    glm::vec2 Scale = m_WordDebug->GetScale();
    int WordSize = m_WordDebug->GetWords().size();
    for(int i=0;i<WordSize;i++){
        if(m_WordDebug->GetWords()[i] == ' '){
            Xscale = 0,Yscale++;
            continue;
        }
        glm::vec2 WordPosition = {WordInitialPosition.x + 8*Scale.x*Xscale,WordInitialPosition.y - 8*Scale.y*Yscale};
        m_WordDebug->SetPosition(i,WordPosition);
        Xscale++;
    }
}