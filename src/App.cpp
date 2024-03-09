#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

#include "pch.hpp"

void App::Start() {

    LOG_TRACE("Start");


    // if m_StartBackground not loaded
    if (!m_StartBackground) {
        m_StartBackground = std::make_shared<AnimatedObject>(
            std::vector<std::string>{RESOURCE_DIR "/Picture/UI/Title1.png",
                                     RESOURCE_DIR "/Picture/UI/Title2.png"},
            true, 300);
        m_StartBackground->SetScale({3, 3});
        m_Root.AddChild(m_StartBackground);
    }

    // render windows
    m_Root.Update();

    // detect enter key to turn next phase
    if (Util::Input::IsKeyUp(Util::Keycode::RETURN)) {
        m_CurrentState = State::UPDATE;

        // free resource
        m_Root.RemoveChild(m_StartBackground);
        m_StartBackground.reset();
    }



}

void App::Update() {
    /*
     * Initial Map.
     */

    std::vector<std::vector<int>> a(16,std::vector<int>(14,3)); //Test spawning map.
    m_Map = std::make_shared<Backgroundmap>(a,"Bomb Man Stage");
    m_Map->SetImageToMap(true);
    m_Root.AddChildren(m_Map->GetChildren());

    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {

    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {


    }
    if(Util::Input::IsKeyPressed(Util::Keycode::UP)) {

    }
    if(Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {

    }
    m_Root.Update();

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_DEBUG("End");
}
