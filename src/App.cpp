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

    // TODO : free resources when change phase
    if (Util::Input::IsKeyUp(Util::Keycode::UP)) { // win game
        m_CurrentState = State::ENDING_ANIMATION;
    }
    if (Util::Input::IsKeyUp(Util::Keycode::DOWN)) { // lose game
        m_CurrentState = State::GAME_LOSE;
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

void App::End() {}
