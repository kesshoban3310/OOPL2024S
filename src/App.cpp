#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");
    m_BackGround = std::make_shared<BackGroundImage>(RESOURCE_DIR"/Picture/Map/Bomb Man Stage.png");
    m_BackGround->SetZIndex(-10);
    m_BackGround->SetVisible(0);
    m_Root.AddChild(m_BackGround);
    std::vector<std::vector<int>> a ={{2,2},{2,2}};
    m_Map = std::make_shared<BackGroundMap>(a,"Bomb Man Stage");
    m_Map->SetImageToMap();
    m_Root.AddChildren(m_Map->GetChildren());
    m_CurrentState = State::UPDATE;
}

void App::Update() {

    // TODO: do your things here and delete this line <3
    if(Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        auto tmp = m_BackGround->GetPosition();
        tmp.x += 5;
        m_BackGround->SetPosition({tmp.x, tmp.y});
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        auto tmp = m_BackGround->GetPosition();
        tmp.x -= 5;
        m_BackGround->SetPosition({tmp.x, tmp.y});
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        auto tmp = m_BackGround->GetPosition();
        tmp.y -= 5;
        m_BackGround->SetPosition({tmp.x, tmp.y});
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        auto tmp = m_BackGround->GetPosition();
        tmp.y += 5;
        m_BackGround->SetPosition({tmp.x, tmp.y});
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
