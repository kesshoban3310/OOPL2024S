#include "PhaseStage.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

void PhaseStage::Init(App *app) {
    // Load the map
    m_BackgroundObjects = std::make_shared<Backgroundmap>("Bomb Man Stage");
    m_ForegroundObjects = std::make_shared<Backgroundmap>("Bomb Man Stage");

    // Load Rockman
    m_Rockman = std::make_shared<Rockman>(glm::vec2{360, -2688},Rockman::LiveState::Initial);

    //Load Rockman Healthbar
    m_RockmanHealthBar = std::make_shared<HealthBar>(glm::vec2{360 - 311, -3408 + 201},"/Picture/Character/Health/blood",29);

    // Load Scorebar
    m_Scorebar = std::make_shared<Scorebar>(glm::vec2{360, -3408});
    // Lode Testbox
    m_Testbox = std::make_shared<TestBox>(glm::vec2{360, -3408}, glm::vec2{3, 3});
    m_BackgroundObjects->SetImagetoBackgroundObject();
    m_ForegroundObjects->SetImagetoForegroundObject();
    // Load Blaster
    for (int i = 0; i < 4; i++) {
        int timer = 66;
        std::shared_ptr<Blaster> blaster = std::make_shared<Blaster>(
            glm::vec2{4894, -2832 + 96 * i}, timer, i % 2);
        m_Blaster.push_back(blaster);
        app->GetRoot()->AddChild(blaster->GetChild());
    }
    // Load Screwdriver
    for (int i = 0; i < 3; i++) {
        std::shared_ptr<Screwdriver> screwdriver =
            std::make_shared<Screwdriver>(glm::vec2{4295 + 301.5 * i, -3602});
        m_Screwdriver.push_back(screwdriver);
        app->GetRoot()->AddChild(screwdriver->GetChild());
    }
    // Load Bombombomb
    for (int i = 0; i < 4; i++) {
        std::shared_ptr<Bombombomb> bombombomb = std::make_shared<Bombombomb>(
            glm::vec2{2515 + 385 * i, -3950}, glm::vec2{0, 12},
            glm::vec2{16, 16}, glm::vec2{3, 3},
            "/Picture/Enemies/Bomb Man Stage/Bombombomb/bomb1.png",
            "/Picture/Enemies/Bomb Man Stage/Bombombomb/bomb2.png");
        m_Bombombomb.push_back(bombombomb);
        app->GetRoot()->AddChild(bombombomb->GetChild());
        app->GetRoot()->AddChildren(bombombomb->GetAmmos());
    }
    //Load OctopusBattery
    glm::vec2 OctopusBatteryIniPos = glm::vec2{12576,-959};
    glm::vec2 OctopusBatteryFinPos = glm::vec2{12720,-959};
    OctopusBattery::OctopusState OctopusIniState = OctopusBattery::OctopusState::SLEEP;
    for(int i=0;i<4;i++){
        if(i%2)
            OctopusIniState = OctopusBattery::OctopusState::BLEAZY;
        else
            OctopusIniState = OctopusBattery::OctopusState::SLEEP;
        std::shared_ptr<OctopusBattery> octopusbattery = std::make_shared<OctopusBattery>(
            OctopusBatteryIniPos,OctopusBatteryFinPos, glm::vec2{16, 0}, glm::vec2{3, 3},
            std::vector<std::string>{
                RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/OctopusBattery/OctopusBattery1.png",
                RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/OctopusBattery/OctopusBattery2.png",
                RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/OctopusBattery/OctopusBattery3.png"},
            OctopusIniState);
        if(i == 0){
            OctopusBatteryIniPos = glm::vec2{12576 ,-1149};
            OctopusBatteryFinPos = glm::vec2{12720 ,-1149};
        }
        else{
            OctopusBatteryIniPos.y-=96;
            OctopusBatteryFinPos.y-=96;
        }
        std::swap(OctopusBatteryIniPos,OctopusBatteryFinPos);
        m_OctopusBattery.push_back(octopusbattery);
        app->GetRoot()->AddChild(octopusbattery->GetChild());
    }
    OctopusBatteryIniPos = glm::vec2{12576 ,-1728};
    OctopusBatteryFinPos = glm::vec2{12720 ,-1728};

    for(int i=0;i<4;i++){
        if(i%2)
            OctopusIniState = OctopusBattery::OctopusState::BLEAZY;
        else
            OctopusIniState = OctopusBattery::OctopusState::SLEEP;
        std::shared_ptr<OctopusBattery> octopusbattery = std::make_shared<OctopusBattery>(
            OctopusBatteryIniPos,OctopusBatteryFinPos, glm::vec2{16, 0}, glm::vec2{3, 3},
            std::vector<std::string>{
                RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/OctopusBattery/OctopusBattery1.png",
                RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/OctopusBattery/OctopusBattery2.png",
                RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/OctopusBattery/OctopusBattery3.png"},
            OctopusIniState);
        if(i == 0){
            OctopusBatteryIniPos = glm::vec2{12576 ,-1918};
            OctopusBatteryFinPos = glm::vec2{12720 ,-1918};
        }
        else{
            OctopusBatteryIniPos.y-=96;
            OctopusBatteryFinPos.y-=96;
        }
        std::swap(OctopusBatteryIniPos,OctopusBatteryFinPos);
        m_OctopusBattery.push_back(octopusbattery);
        app->GetRoot()->AddChild(octopusbattery->GetChild());
    }

    // Add the root
    m_Rockman->Behavior(m_ForegroundObjects->GetCollisonBox(glm::vec2{360, -3408}));
    m_Scorebar->Show({360, -3408});
    app->GetRoot()->AddChild(m_Testbox->Getchild());
    app->GetRoot()->AddChildren(m_BackgroundObjects->GetChildren());
    app->GetRoot()->AddChildren(m_ForegroundObjects->GetChildren());
    app->GetRoot()->AddChildren(m_Rockman->GetAllChildren());
    app->GetRoot()->AddChildren(m_Scorebar->GetChildren());
    app->GetRoot()->AddChild(m_RockmanHealthBar->GetChild());

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
    m_SceneManager.Update(m_Rockman->GetPosition());
    app->SetCameraPosition(m_SceneManager.GetCameraPosition());

    //get some info
    glm::vec2 CameraPos = app->GetCameraPosition();

    // show healthbar and scorebar
    m_Scorebar->Show(CameraPos);
    m_RockmanHealthBar->SetPosition(glm::vec2 {CameraPos.x-311,CameraPos.y+201});

    // if changing scene, return
    if (m_SceneManager.IsChangingScene()) {
        LOG_DEBUG("Changing Scene");
        return;
    }

    m_Rockman->Behavior(m_ForegroundObjects->GetCollisonBox(app->GetCameraPosition()));
    for (int i = 0; i < 4; i++) {
        m_Blaster[i]->Behavior(m_Rockman->GetPosition());
    }
    for (int i = 0; i < 4; i++) {
        m_Bombombomb[i]->Behavior(CameraPos);
    }
    for (int i = 0; i < 3; i++) {
        m_Screwdriver[i]->Behavior(m_Rockman->GetPosition());
    }

    for(int i=0;i<8;i++){
        m_OctopusBattery[i]->Behavior(CameraPos);
    }

    ReloadMagazine(app);

    //m_Testbox->Move();

    /*
    LOG_INFO("Camera Position");
    LOG_INFO(std::to_string(app->GetCameraPosition().x)+" "+std::to_string(app->GetCameraPosition().y));
    LOG_INFO("Rockman Position");
    LOG_INFO(std::to_string(m_Rockman->Getposition().x)+" "+std::to_string(m_Rockman->Getposition().y));
    LOG_INFO("Root Size");
    LOG_INFO(std::to_string(app->GetRoot()->size()));
    LOG_INFO("Bombombomb Position");
    LOG_INFO(std::to_string(m_Bombombomb[0]->GetPosition().x)+" "+std::to_string(m_Bombombomb[0]->GetPosition().y));
    */
    if (Util::Input::IsKeyPressed(Util::Keycode::B))
        m_Rockman->SetPosition(app->GetCameraPosition());
    if (Util::Input::IsKeyPressed(Util::Keycode::L)) {
        m_Rockman->SetPosition({12638, -398});
        m_Testbox->SetPosition({12638, -398});
    }

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
void PhaseStage::ReloadMagazine(App *app) {
    glm::vec2 CameraPosition = app->GetCameraPosition();
    auto magazine = m_Rockman->GetAmmo();
    for (auto Ammo : magazine) {
        m_Magazine.push(Ammo);
        app->GetRoot()->AddChild(Ammo->GetChild());
    }
    for (int i = 0; i < 4; i++) { // Blaster Magazine
        magazine = m_Blaster[i]->Getammo();
        for (auto Ammo : magazine) {
            m_Magazine.push(Ammo);
            app->GetRoot()->AddChild(Ammo->GetChild());
        }
    }
    for (int i = 0; i < 3; i++) { // Screwdriver Magazine
        magazine = m_Screwdriver[i]->Getammo();
        for (auto Ammo : magazine) {
            m_Magazine.push(Ammo);
            app->GetRoot()->AddChild(Ammo->GetChild());
        }
    }
    int magazine_size = m_Magazine.size();
    for (int i = 0; i < magazine_size; i++) {
        auto Ammo = m_Magazine.front();
        m_Magazine.pop();
        Ammo->Behavior();
        if (Ammo->Outofrange(CameraPosition)) {
            app->GetRoot()->RemoveChild(Ammo->GetChild());
            continue;
        }
        m_Magazine.push(Ammo);
    }
}
