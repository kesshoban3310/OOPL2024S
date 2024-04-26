#include "PhaseStage.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

void PhaseStage::Init(App *app) {
    // Load the map
    m_BackgroundObjects = std::make_shared<Backgroundmap>("Bomb Man Stage");
    m_ForegroundObjects = std::make_shared<Backgroundmap>("Bomb Man Stage");

    // Load Rockman
    m_Rockman = std::make_shared<Rockman>(glm::vec2{360, -3408},
                                          Rockman::State::Initial);
    // Load Scorebar
    m_Scorebar = std::make_shared<Scorebar>(glm::vec2{360, -3408});
    // m_Testbox = std::make_shared<TestBox>(glm::vec2 {415,-3408},glm::vec2
    // {3,3});

    m_BackgroundObjects->SetImagetoBackgroundObject();
    m_ForegroundObjects->SetImagetoForegroundObject();

    // Add the root
    m_Rockman->behavior();
    m_Scorebar->Show({360, -3408});
    // app->GetRoot()->AddChild(m_Testbox->Getchild());
    app->GetRoot()->AddChildren(m_BackgroundObjects->GetChildren());
    app->GetRoot()->AddChildren(m_ForegroundObjects->GetChildren());

    app->GetRoot()->AddChildren(m_Rockman->GetAllchildren());
    app->GetRoot()->AddChildren(m_Scorebar->Getchildren());
    // TODO: remove camera movement in the futures
    app->SetCameraPosition({360, -3408});

    m_SceneManager.SetSceneRanges({
        {0, {{-24, -3048}, {5352, -3816}}},
        {1, {{4584, -2280}, {5352, -3048}}},
        {2, {{4584, -1512}, {9192, -2280}}},
        {3, {{8424, -744}, {9192, -1512}}},
        {4, {{8424, 24}, {12264, -744}}},
        {5, {{12264, 24}, {13032, -744}}},
        {6, {{12264, -744}, {13032, -1512}}},
        {7, {{12264, -1512}, {13032, -2280}}},
        {8, {{12264, -2280}, {13032, -3048}}},
    });
}

void PhaseStage::Update(App *app) {
    // update SceneManager
    m_SceneManager.Update(m_Rockman->Getposition());
    app->SetCameraPosition(m_SceneManager.GetCameraPosition());

    // show healthbar and scorebar
    m_Rockman->GetHealthbar()->SetPosition(app->GetCameraPosition());
    m_Scorebar->Show(app->GetCameraPosition());

    // if changing scene, return
    if (m_SceneManager.IsChangingScene()) {
        LOG_DEBUG("Changing Scene");
        return;
    }

    m_Rockman->behavior();
    LOG_DEBUG("{}, {}", m_Rockman->Getposition().x, m_Rockman->Getposition().y);

    // m_Testbox->Move();

    /*
    LOG_DEBUG("Camera Position");
    LOG_DEBUG(std::to_string(app->GetCameraPosition().x)+"
    "+std::to_string(app->GetCameraPosition().y)); LOG_DEBUG("Rockman
    Position"); LOG_DEBUG(std::to_string(m_Rockman->Getposition().x)+"
    "+std::to_string(m_Rockman->Getposition().y)); LOG_DEBUG("Root Size");
    LOG_DEBUG(std::to_string(app->GetRoot()->size()));
    */

    /*
    std::shared_ptr<Collider> Boxbox = m_Testbox->Getcollisonbox();
    std::shared_ptr<Collider> Rockmanupbox = m_Rockman->GetCollider()[0];
    std::shared_ptr<Collider> Rockmandownbox = m_Rockman->GetCollider()[1];

    if(IsColliding(*Boxbox,*Rockmanupbox))
        LOG_DEBUG("Up Collison");
    if(IsColliding(*Boxbox,*Rockmandownbox))
        LOG_DEBUG("Down Collison");
    */

    // TODO : change this to win
    if (Util::Input::IsKeyUp(Util::Keycode::I)) {
        app->ChangeState(App::State::ENDING_ANIMATION);
        return;
    }

    // TODO : change this to lose
    if (Util::Input::IsKeyUp(Util::Keycode::O)) {
        app->ChangeState(App::State::LOSE);
        return;
    }
}

void PhaseStage::Leave(App *app) {
    // clean up root
    app->GetRoot()->RemoveAllChildren();
}
