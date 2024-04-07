#include "PhaseTitle.hpp"
#include "Util/Input.hpp"

void PhaseTitle::Init(App *app) {
    // init background
    m_Background = std::make_shared<AnimatedObject>(
        std::vector<std::string>{RESOURCE_DIR "/Picture/UI/Title1.png",
                                 RESOURCE_DIR "/Picture/UI/Title2.png"},
        true, 500);
    m_Background->SetScale({3, 3});
    app->GetRoot()->AddChild(m_Background);

    // set audio
    m_BGM = std::make_shared<Util::BGM>(RESOURCE_DIR"/Sound/Title.mp3");
    m_BGM->Play(1);
}

void PhaseTitle::Update(App *app) {
    // if enter is pressed
    if (Util::Input::IsKeyUp(Util::Keycode::RETURN)) {
        app->ChangeState(App::State::MENU);
        return;
    }
}

void PhaseTitle::Leave(App *app) {
    // stop audio
    m_BGM->Pause();

    // free resources
    m_Background = nullptr;
    m_BGM = nullptr;

    app->GetRoot()->RemoveAllChildren();
}
