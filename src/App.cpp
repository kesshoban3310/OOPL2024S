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
    // LOG_DEBUG("Update");
    if (!m_Tile) {
        m_Tile = std::make_shared<ImageObject>(
            RESOURCE_DIR "/Picture/Tiles/Bomb Man Stage/Background/2.png");
        m_Tile->SetPosition(Tilemap::GetTilePosition(0, 0));
        m_Tile->SetScale({3, 3});
        m_Root.AddChild(m_Tile);
    }

    m_Root.Update();
    // Do not touch the code below as they serve the purpose for closing the
    // window.
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_DEBUG("End");
}
