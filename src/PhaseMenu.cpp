#include "PhaseMenu.hpp"
#include "Util/Input.hpp"

void PhaseMenu::Init(App *app) {
    // init tables
    m_NextStage = {
        {Stage::CUTMAN, Stage::GUTSMAN},
        {Stage::GUTSMAN, Stage::ICEMAN},
        {Stage::ICEMAN, Stage::BOMBMAN},
        {Stage::BOMBMAN, Stage::FIREMAN},
        {Stage::FIREMAN, Stage::ELECMAN},
        {Stage::ELECMAN, Stage::CUTMAN}
    };
    m_PreviousStage = {
        {Stage::CUTMAN, Stage::ELECMAN},
        {Stage::GUTSMAN, Stage::CUTMAN},
        {Stage::ICEMAN, Stage::GUTSMAN},
        {Stage::BOMBMAN, Stage::ICEMAN},
        {Stage::FIREMAN, Stage::BOMBMAN},
        {Stage::ELECMAN, Stage::FIREMAN}
    };
    m_SelectBoxPosition = {
        {Stage::CUTMAN, {-96, 216}},
        {Stage::GUTSMAN, {96, 216}},
        {Stage::ICEMAN, {192, 24}},
        {Stage::BOMBMAN, {96, -168}},
        {Stage::FIREMAN, {-96, -168}},
        {Stage::ELECMAN, {-192, 24}}
    };

    // init stage state
    m_Stage = Stage::CUTMAN;

    // init screen
    m_Screen = std::make_shared<AnimatedObject>(
        std::vector<std::string>{RESOURCE_DIR "/Picture/UI/Menu1.png",
                                 RESOURCE_DIR "/Picture/UI/Menu2.png"},
        false, 300);
    m_Screen->SetScale({3, 3});

    // init select box
    m_SelectBox = std::make_shared<AnimatedObject>(
        std::vector<std::string>{RESOURCE_DIR "/Picture/UI/Select Box1.png",
                                 RESOURCE_DIR "/Picture/UI/Select Box2.png"},
        false, 300);
    m_SelectBox->SetScale({3, 3});
    m_SelectBox->SetPosition({-3 * 64, 3 * 8});

    // play animation
    m_Screen->PlayAnimation();
    m_SelectBox->PlayAnimation();

    // add to root
    app->GetRoot()->AddChild(m_Screen);
    app->GetRoot()->AddChild(m_SelectBox);


    // set audio
    m_BGM = std::make_shared<Util::BGM>(RESOURCE_DIR "/Sound/Menu.mp3");
    m_BGM->Play();
}

void PhaseMenu::Update(App *app) {
    // change stage
    if(Util::Input::IsKeyDown(Util::Keycode::LEFT)) {
        m_Stage = m_PreviousStage[m_Stage];
        m_Screen->ResetAnimation();
        m_SelectBox->ResetAnimation();
    }
    if(Util::Input::IsKeyDown(Util::Keycode::RIGHT)) {
        m_Stage = m_NextStage[m_Stage];
        m_Screen->ResetAnimation();
        m_SelectBox->ResetAnimation();
    }

    // set position
    m_SelectBox->SetPosition(m_SelectBoxPosition[m_Stage]);

    // change app state
    // TODO: add more state if there are more stages
    // TODO: add background change to cleared stage
    if(Util::Input::IsKeyDown(Util::Keycode::RETURN)) {
        app->ChangeState(App::State::STAGE);
    }
}

void PhaseMenu::Leave(App *app) {
    // stop audio
    m_BGM->Pause();

    // free resources
    m_Screen = nullptr;
    m_SelectBox = nullptr;
    m_BGM = nullptr;
    app->GetRoot()->RemoveAllChildren();
}
