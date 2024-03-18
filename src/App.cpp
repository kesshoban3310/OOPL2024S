#include "App.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

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
    if (!m_Converter) {
        m_Converter =
            std::make_shared<Txtconverter>(RESOURCE_DIR "/Map/test.txt");
    }
    if (!m_Map) {
        // Test spawning map.

        m_Map = std::make_shared<Backgroundmap>(m_Converter->convert(),
                                                "Bomb Man Stage");
        m_Map->SetImageToMap(true);
        m_Root.AddChildren(m_Map->GetChildren());
    }
    // Initialize Rock man.
    if (!m_Rockman) {
        m_Rockman = std::make_shared<Rockman>();
        m_Rockman->Initialize();
        m_Root.AddChildren(m_Rockman->Getchildren());
    }
    /**
     *  @brief Test Rockman move and posture.
     */

    m_Rockman->move();

    if (NoKeyPress()) { //if no key pressed, then reset rock man's module.
        m_Rockman->Setvisable(0);
    }
    // render windows
    m_Root.Update();

    // TODO: win game -> ENDING_ANIMATION
    // lose game -> GAME_LOSE
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
        // free resources.
        std::vector<std::shared_ptr<Util::GameObject>> map_child =
            m_Map->GetChildren();
        for (auto i : map_child)
            m_Root.RemoveChild(i);

        std::vector<std::shared_ptr<Util::GameObject>> rockman_child =
            m_Rockman->Getchildren();
        for (auto i : rockman_child)
            m_Root.RemoveChild(i);

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

bool App::NoKeyPress() {
    return !Util::Input::IsKeyPressed(Util::Keycode::LEFT) &&
           !Util::Input::IsKeyPressed(Util::Keycode::RIGHT) &&
           !Util::Input::IsKeyPressed(Util::Keycode::DOWN) &&
           !Util::Input::IsKeyPressed(Util::Keycode::UP);
}
