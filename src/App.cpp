#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    background = std::make_shared<AnimatedObject>(
        std::vector<std::string>{RESOURCE_DIR "/Picture/UI/Title1.png",
                                 RESOURCE_DIR "/Picture/UI/Title2.png"},
        true, 250, true);
    background->SetScale({3, 3});
    m_Root.AddChild(background);
    m_CurrentState = State::UPDATE;
}

void App::Update() {

    if (Util::Input::IsKeyDown(Util::Keycode::RETURN)) {
       background->ResetAnimation();
       background->PlayAnimation();
       background->SetLooping(false);
    }
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
