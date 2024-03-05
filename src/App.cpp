#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_CurrentState = State::UPDATE;

    background = std::make_shared<AnimatedObject>( std::vector<std::string>
        {RESOURCE_DIR"/Picture/UI/Title1.png", RESOURCE_DIR"/Picture/UI/Title2.png"});
    background->SetScale({3, 3});
    m_Root.AddChild(background);
}

void App::Update() {

    m_Root.Update();

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
