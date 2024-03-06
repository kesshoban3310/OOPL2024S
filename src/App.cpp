#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    background.push_back(std::make_shared<ImageObject>(RESOURCE_DIR "/Picture/Tiles/Bomb Man Stage/Background/2.png"));
    background.back()->SetScale({3, 3});
    background.back()->SetPosition({-3 * 8 * 15, 3 * 8 * 13});
    m_Root.AddChild(background.back());
    for(int i=0; i<16; i++) {
        background.push_back(std::make_shared<ImageObject>(RESOURCE_DIR "/Picture/Tiles/Bomb Man Stage/Background/2.png"));
        background.back()->SetScale({3, 3});
        background.back()->SetPosition({3 * 16 * i - 3 * 8 * 15, -100});
        m_Root.AddChild(background.back());
    }
    for(int i=0; i<15; i++) {
        background.push_back(std::make_shared<ImageObject>(RESOURCE_DIR "/Picture/Tiles/Bomb Man Stage/Background/2.png"));
        background.back()->SetScale({3, 3});
        background.back()->SetPosition({3 * 16 * i - 3 * 8 * 15, 0});
        m_Root.AddChild(background.back());
    }
    m_CurrentState = State::UPDATE;
}

void App::Update() {

    if (Util::Input::IsKeyDown(Util::Keycode::RETURN)) {

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
