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

// TODO : clean up code here, it's messy
void App::EndingAnimation() {
    if (!m_EndAnimationBackground) {
        m_EndAnimationBackground = std::make_shared<ImageObject>(
            RESOURCE_DIR "/Picture/UI/Credits/background.png");
        m_EndAnimationBackground->SetScale({3, 3});
        m_EndAnimationBackground->SetPosition({-3840, 0});
        m_EndAnimationBackground->SetZIndex(0);
        m_Root.AddChild(m_EndAnimationBackground);
    }
    if (!m_EndAnimationCharacter) {
        m_EndAnimationCharacter = std::make_shared<AnimatedObject>(
            std::vector<std::string>{
                RESOURCE_DIR "/Picture/Character/Normal/Walk2.png",
                RESOURCE_DIR "/Picture/Character/Normal/Walk1.png",
                RESOURCE_DIR "/Picture/Character/Normal/Walk2.png",
                RESOURCE_DIR "/Picture/Character/Normal/Walk3.png",
            },
            true, 120);
        m_EndAnimationCharacter->SetScale({3, 3});
        m_EndAnimationCharacter->SetZIndex(10);
        m_EndAnimationCharacter->SetPosition({0, 30});
        m_Root.AddChild(m_EndAnimationCharacter);
    }
    if (m_EndAnimationBackground->GetPosition().x +
            Util::Time::GetDeltaTime() * 120 >=
        3840) {
        m_EndAnimationBackground->SetPosition({3840.0, 0});
        m_EndAnimationCharacter->SetAnimation(
            std::vector<std::string>{
                RESOURCE_DIR "/Picture/Character/Normal/Idle1.png"},
            false, -1);
        scrolling = false;
    }
    if (scrolling) {
        m_EndAnimationBackground->SetPosition(
            {m_EndAnimationBackground->GetPosition().x +
                 Util::Time::GetDeltaTime() * 120,
             0});
    }
    m_Root.Update();
    if (Util::Input::IsKeyUp(Util::Keycode::RETURN)) {
        m_CurrentState = State::END;
        m_Root.RemoveChild(m_EndAnimationBackground);
        m_EndAnimationBackground.reset();
    }
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
