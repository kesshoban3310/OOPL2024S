#include "PhaseEndingAnimation.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

void PhaseEndingAnimation::Init(App *app) {
    // init scrolling
    m_IsScrolling = true;

    // init background
    m_Background = std::make_shared<ImageObject>(
        RESOURCE_DIR "/Picture/UI/Credits.png");
    m_Background->SetScale({3, 3});
    m_Background->SetPosition({-3840, 0});
    m_Background->SetZIndex(0);
    app->GetRoot()->AddChild(m_Background);

    // init character
    m_Character = std::make_shared<AnimatedObject>(
        std::vector<std::string>{
            RESOURCE_DIR "/Picture/Character/Normal/Walk2.png",
            RESOURCE_DIR "/Picture/Character/Normal/Walk1.png",
            RESOURCE_DIR "/Picture/Character/Normal/Walk2.png",
            RESOURCE_DIR "/Picture/Character/Normal/Walk3.png",
        },
        true, 120);
    std::dynamic_pointer_cast<AnimatedObject>(m_Character)->SetScale({3, 3});
    std::dynamic_pointer_cast<AnimatedObject>(m_Character)
        ->SetPosition({0, 30});
    m_Character->SetZIndex(10);
    app->GetRoot()->AddChild(m_Character);

    m_BGM = std::make_shared<Util::BGM>(RESOURCE_DIR"/Sound/Ending Animation.mp3");
    m_BGM->Play(1);
}

void PhaseEndingAnimation::Update(App *app) {
    // calculate delta x for scrolling
    double delta_x = Util::Time::GetDeltaTime() * 121;

    // if background is out of screen and not scrolling
    if (m_Background->GetPosition().x + delta_x >= 3840 && m_IsScrolling) {
        // set background to border of screen
        m_Background->SetPosition({3840, 0});

        // set character to idle
        app->GetRoot()->RemoveChild(m_Character);
        m_Character = std::make_shared<ImageObject>(
            RESOURCE_DIR "/Picture/Character/Normal/Idle1.png");
        std::dynamic_pointer_cast<ImageObject>(m_Character)->SetScale({3, 3});
        std::dynamic_pointer_cast<ImageObject>(m_Character)
            ->SetPosition({0, 30});
        m_Character->SetZIndex(10);
        app->GetRoot()->AddChild(m_Character);

        // stop scrolling
        m_IsScrolling = false;
    }

    // if scrolling
    if (m_IsScrolling) {
        // scroll background
        m_Background->SetPosition({m_Background->GetPosition().x + delta_x, 0});
    }

    // if enter key is pressed and not scrolling
    if (Util::Input::IsKeyUp(Util::Keycode::RETURN) && !m_IsScrolling) {
        // exit app
        app->GetContext()->SetExit(true);
        return;
    }
}

void PhaseEndingAnimation::Leave(App *app) {
    // stop bgm
    m_BGM->Pause();

    // free resources
    m_Background = nullptr;
    m_Character = nullptr;
    m_BGM = nullptr;

    // remove all children from root
    app->GetRoot()->RemoveAllChildren();
}
