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
        m_CurrentState = State::GAME_STAGE_SELECT;

        // free resource
        m_Root.RemoveChild(m_StartBackground);
        m_StartBackground.reset();
    }
}

void App::GameStageSelect() {
    m_CurrentState = State::GAME_STAGE;
}

void App::GameStage() {
    /*
     * Initialize Map.
     */
    if (!m_converter) {
        m_converter =
            std::make_shared<Txtconverter>(RESOURCE_DIR "/Map/test.txt");
    }
    if (!m_Map) {
        // Test spawning map.
        std::vector<std::vector<int>> a(16, std::vector<int>(14, 3));
        m_Map = std::make_shared<Backgroundmap>(m_converter->convert(),
                                                "Bomb Man Stage");
        m_Map->SetImageToMap(true);
        m_Root.AddChildren(m_Map->GetChildren());
    }

    // render windows
    m_Root.Update();

    // TODO: win game -> ENDING_ANIMATION
    // lose game -> GAME_LOSE
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::GameLose() {
    m_CurrentState = State::ENDING_ANIMATION;
}

void App::EndingAnimation() {
    m_CurrentState = State::END;
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_DEBUG("End");
}
