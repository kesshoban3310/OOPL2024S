#include "App.hpp"

#include "Component/Tilemap.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
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
    if(!m_Map) {
        std::vector<std::vector<int>> a = {{2, 2}, {2, 2}};
        m_Map = std::make_shared<BackGroundMap>(a,"Bomb Man Stage");
        m_Map->SetImageToMap();
        m_Root.AddChildren(m_Map->GetChildren());
    }

    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        m_Map->Move(5,0);
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        m_Map->Move(-5,0);
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        m_Map->Move(0,-5);
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        m_Map->Move(0,5);
    }

    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    m_Root.Update();

    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_DEBUG("End");
}
