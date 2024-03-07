#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    //
    //  Try to test how to spawn map.
    //
    std::vector<std::vector<int>> a(14,{3,4,2,6});
    m_Map = std::make_shared<BackGroundMap>(a,"Bomb Man Stage");
    m_Map->SetImageToMap();
    m_Root.AddChildren(m_Map->GetChildren());

    m_CurrentState = State::UPDATE;
}

void App::Update() {

    // TODO: do your things here and delete this line <3
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
    LOG_TRACE("End");
}
