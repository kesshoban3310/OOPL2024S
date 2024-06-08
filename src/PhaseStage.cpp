#include "PhaseStage.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

void PhaseStage::Init(App *app) {
    // Load the map
    m_BackgroundObjects = std::make_shared<Backgroundmap>("Bomb Man Stage");
    m_ForegroundObjects = std::make_shared<Backgroundmap>("Bomb Man Stage");

    // Load Rockman
    m_Rockman = std::make_shared<Rockman>(glm::vec2{360, -2688},
                                          Rockman::LiveState::Initial);

    // Load Rockman Healthbar
    m_RockmanHealthBar =
        std::make_shared<HealthBar>(glm::vec2{360 - 311, -3408 + 201},
                                    "/Picture/Character/Health/blood", 29);

    // Load Scorebar
    m_Scorebar = std::make_shared<Scorebar>(glm::vec2{360, -3408});
    // Lode Testbox
    m_Testbox =
        std::make_shared<TestBox>(glm::vec2{360, -3477.5}, glm::vec2{3, 3});

    // Load Map
    m_BackgroundObjects->SetImagetoBackgroundObject();
    m_ForegroundObjects->SetImagetoForegroundObject();
    m_ForeObjectTileBox = m_ForegroundObjects->GetTileBox();

    // Load Kamadoma
    std::vector<std::string> KamadomaPath;
    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR
                           "/Picture/Enemies/Bomb Man Stage/Kamadoma/Kamadoma" +
                           std::to_string(i) + ".png";
        KamadomaPath.push_back(path);
    }
    std::vector<glm::vec2> KamadomaPoints;
    KamadomaPoints = {
        glm::vec2{72, -3600},   glm::vec2{312, -3600},  glm::vec2{600, -3600},
        glm::vec2{835, -3504},  glm::vec2{1031, -3408}, glm::vec2{1226, -3312},
        glm::vec2{1356, -3412}, glm::vec2{1461, -3506}, glm::vec2{1607, -3600},
        glm::vec2{1850, -3600}, glm::vec2{2132, -3600}};
    for(int i=0;i<5;i++){
        std::shared_ptr<Kamadoma> kamadoma = std::make_shared<Kamadoma>(
            KamadomaPath, KamadomaPoints, KamadomaPoints[3+i],3+i,
            glm::vec2{16 * 3, 16 * 3}, 1, true, Enemy::HurtState::COWARDLY);
        m_Kamadoma.push_back(kamadoma);
        m_Enemies.push_back(kamadoma);
        app->GetRoot()->AddChild(kamadoma->GetChild());
    }
    // Load Blaster
    std::vector<std::string> BlasterPath;
    for (int i = 1; i <= 4; i++) {
        std::string path = RESOURCE_DIR
                           "/Picture/Enemies/Bomb Man Stage/blaster/blaster" +
                           std::to_string(i) + ".png";
        BlasterPath.push_back(path);
    }
    std::string BlasterAmmoPath =
        RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/blaster/blaster5.png";
    for (int i = 0; i < 4; i++) {
        int timer = 66;
        std::shared_ptr<Blaster> blaster = std::make_shared<Blaster>(
            glm::vec2{4894, -2832 + 96 * i}, glm::vec2{16 * 3, 16 * 3},
            glm::vec2{-3, 3}, timer, i % 2, BlasterPath, BlasterAmmoPath, 1,
            true, Enemy::HurtState::INVINCIBLE, Enemy::LifeState::LIFE);
        m_Blaster.push_back(blaster);
        m_Enemies.push_back(blaster);
        app->GetRoot()->AddChild(blaster->GetChild());
    }

    // Load Screwdriver
    std::vector<std::string> ScrewDriverPath;
    for (int i = 1; i <= 5; i++) {
        std::string path =
            RESOURCE_DIR
            "/Picture/Enemies/Bomb Man Stage/ScrewDriver/ScrewDriver" +
            std::to_string(i) + ".png";
        ScrewDriverPath.push_back(path);
    }
    std::string ScrewDriverAmmoPath = RESOURCE_DIR
        "/Picture/Enemies/Bomb Man Stage/ScrewDriver/ScrewDriver6.png";

    for (int i = 0; i < 3; i++) {
        std::shared_ptr<Screwdriver> screwdriver =
            std::make_shared<Screwdriver>(
                glm::vec2{4295 + 301.5 * i, -3602}, glm::vec2{3, 3},
                glm::vec2{16 * 3, 16 * 3}, ScrewDriverPath, ScrewDriverAmmoPath,
                Enemy::LifeState::LIFE, Enemy::HurtState::COWARDLY, 1, true);
        m_Screwdriver.push_back(screwdriver);
        m_Enemies.push_back(screwdriver);
        app->GetRoot()->AddChild(screwdriver->GetChild());
    }

    // Load Bombombomb
    for (int i = 0; i < 4; i++) {
        std::shared_ptr<Bombombomb> bombombomb = std::make_shared<Bombombomb>(
            glm::vec2{2515 + 385 * i, -3950}, glm::vec2{0, 12},
            glm::vec2{16, 16}, glm::vec2{3, 3}, glm::vec2{16 * 3, 16 * 3},
            RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/Bombombomb/bomb1.png",
            RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/Bombombomb/bomb2.png",
            1, true, Enemy::HurtState::COWARDLY);
        m_Bombombomb.push_back(bombombomb);
        m_Enemies.push_back(bombombomb);
        app->GetRoot()->AddChild(bombombomb->GetChild());
    }
    // Load OctopusBattery
    glm::vec2 OctopusBatteryIniPos = glm::vec2{12576, -959};
    glm::vec2 OctopusBatteryFinPos = glm::vec2{12720, -959};
    OctopusBattery::OctopusState OctopusIniState =
        OctopusBattery::OctopusState::SLEEP;
    for (int i = 0; i < 4; i++) {
        if (i % 2)
            OctopusIniState = OctopusBattery::OctopusState::BLEAZY;
        else
            OctopusIniState = OctopusBattery::OctopusState::SLEEP;
        std::shared_ptr<OctopusBattery> octopusbattery =
            std::make_shared<OctopusBattery>(
                OctopusBatteryIniPos, OctopusBatteryFinPos,
                glm::vec2{16 * 3, 16 * 3}, glm::vec2{16, 0}, glm::vec2{3, 3},
                std::vector<std::string>{
                    RESOURCE_DIR "/Picture/Enemies/Bomb Man "
                                 "Stage/OctopusBattery/OctopusBattery1.png",
                    RESOURCE_DIR "/Picture/Enemies/Bomb Man "
                                 "Stage/OctopusBattery/OctopusBattery2.png",
                    RESOURCE_DIR "/Picture/Enemies/Bomb Man "
                                 "Stage/OctopusBattery/OctopusBattery3.png"},
                1, true, OctopusIniState, Enemy::HurtState::COWARDLY);
        if (i == 0) {
            OctopusBatteryIniPos = glm::vec2{12576, -1149};
            OctopusBatteryFinPos = glm::vec2{12720, -1149};
        }
        else {
            OctopusBatteryIniPos.y -= 96;
            OctopusBatteryFinPos.y -= 96;
        }
        std::swap(OctopusBatteryIniPos, OctopusBatteryFinPos);
        m_OctopusBattery.push_back(octopusbattery);
        m_Enemies.push_back(octopusbattery);
        app->GetRoot()->AddChild(octopusbattery->GetChild());
    }
    OctopusBatteryIniPos = glm::vec2{12576, -1728};
    OctopusBatteryFinPos = glm::vec2{12720, -1728};

    for (int i = 0; i < 4; i++) {
        if (i % 2)
            OctopusIniState = OctopusBattery::OctopusState::BLEAZY;
        else
            OctopusIniState = OctopusBattery::OctopusState::SLEEP;
        std::shared_ptr<OctopusBattery> octopusbattery =
            std::make_shared<OctopusBattery>(
                OctopusBatteryIniPos, OctopusBatteryFinPos,
                glm::vec2{16 * 3, 16 * 3}, glm::vec2{16, 0}, glm::vec2{3, 3},
                std::vector<std::string>{
                    RESOURCE_DIR "/Picture/Enemies/Bomb Man "
                                 "Stage/OctopusBattery/OctopusBattery1.png",
                    RESOURCE_DIR "/Picture/Enemies/Bomb Man "
                                 "Stage/OctopusBattery/OctopusBattery2.png",
                    RESOURCE_DIR "/Picture/Enemies/Bomb Man "
                                 "Stage/OctopusBattery/OctopusBattery3.png"},
                1, true, OctopusIniState, Enemy::HurtState::COWARDLY);
        if (i == 0) {
            OctopusBatteryIniPos = glm::vec2{12576, -1918};
            OctopusBatteryFinPos = glm::vec2{12720, -1918};
        }
        else {
            OctopusBatteryIniPos.y -= 96;
            OctopusBatteryFinPos.y -= 96;
        }
        std::swap(OctopusBatteryIniPos, OctopusBatteryFinPos);
        m_OctopusBattery.push_back(octopusbattery);
        m_Enemies.push_back(octopusbattery);
        app->GetRoot()->AddChild(octopusbattery->GetChild());
    }
    // Load KillerBomb
    m_KillerBomb = std::make_shared<KillerBomb>(
        glm::vec2{6059, -2051}, glm::vec2{-160, 200}, glm::vec2{3, 3},
        RESOURCE_DIR
        "/Picture/Enemies/Bomb Man Stage/KillerBomb/KillerBomb.png",
        1, true);
    m_Enemies.push_back(m_KillerBomb);
    // Loag Mambu
    m_Mambu = std::make_shared<Mambu>(
        glm::vec2{9406, -360},
        std::vector<std::string>{
            RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/Mambu/Mambu1.png",
            RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/Mambu/Mambu2.png"},
        glm::vec2{-80, 0}, glm::vec2{40, 40},
        RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/Mambu/Mambu3.png",
        glm::vec2{3, 3}, 1, true);
    m_Enemies.push_back(m_Mambu);
    // Load Gabyoll
    std::vector<std::string> GabyollPath;
    for (int i = 1; i <= 2; i++) {
        std::string path = RESOURCE_DIR
                           "/Picture/Enemies/Bomb Man Stage/Gabyoll/Gabyoll" +
                           std::to_string(i) + ".png";
        GabyollPath.push_back(path);
    }
    std::vector<std::pair<glm::vec2,glm::vec2> >GabyollPos;
    GabyollPos = {
        {glm::vec2 {8108,-1888},glm::vec2 {8260,-1888}},
        {glm::vec2 {8534,-1744},glm::vec2 {8598,-1744}},
        {glm::vec2 {8936,-2080},glm::vec2 {7962,-2080}},
    };
    for(int i=0;i<3;i++){
        std::shared_ptr<Gabyoll> gabyoll = std::make_shared<Gabyoll>(
            GabyollPos[i].first, GabyollPos[i].second, glm::vec2{16 * 3, 8 * 3},
            GabyollPath, glm::vec2{0, 0}, 1, true, Enemy::HurtState::INVINCIBLE,
            Enemy::LifeState::LIFE);
        m_Enemies.push_back(gabyoll);
        m_Gabyoll.push_back(gabyoll);
        app->GetRoot()->AddChild(gabyoll->GetChild());
    }
    // Load SniperJoe
    std::vector<std::string> SniperJoePath;
    for (int i = 1; i <= 4; i++) {
        std::string path =
            RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/SniperJoe/SniperJoe" +
            std::to_string(i) + ".png";
        SniperJoePath.push_back(path);
    }
    std::string SniperJoeAmmoPath =
        RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/SniperJoe/SniperJoe5.png";
    m_SniperJoe = std::make_shared<SniperJoe>(
        glm::vec2{10460, -323}, glm::vec2{10992, -323},
        glm::vec2{20 * 3, 22 * 3}, glm::vec2{20 * 3, 0 * 3}, glm::vec2{-240, 0},
        SniperJoePath, SniperJoeAmmoPath, 5, true, Enemy::HurtState::INVINCIBLE,
        Enemy::LifeState::LIFE);
    m_Enemies.push_back(m_SniperJoe);
    // Add the root
    m_Scorebar->Show({360, -3408});
    app->GetRoot()->AddChild(m_Testbox->Getchild());
    app->GetRoot()->AddChild(m_RockmanHealthBar->GetChild());
    app->GetRoot()->AddChild(m_KillerBomb->GetChild());
    app->GetRoot()->AddChild(m_Mambu->GetChild());
    app->GetRoot()->AddChild(m_SniperJoe->GetChild());
    app->GetRoot()->AddChildren(m_Rockman->GetAllChildren());
    app->GetRoot()->AddChildren(m_Scorebar->GetChildren());
    app->GetRoot()->AddChildren(m_BackgroundObjects->GetChildren());
    app->GetRoot()->AddChildren(m_ForegroundObjects->GetChildren());

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
    m_EnemyManager.SetEnemies(m_Enemies);

    app->Update();
}

void PhaseStage::Update(App *app) {
    // update SceneManager
    m_SceneManager.Update(m_Rockman->GetPosition());
    app->SetCameraPosition(m_SceneManager.GetCameraPosition());
    // get some info
    glm::vec2 CameraPos = app->GetCameraPosition();

    // show healthbar and scorebar
    m_Scorebar->Show(CameraPos);
    m_RockmanHealthBar->SetPosition(
        glm::vec2{CameraPos.x - 311, CameraPos.y + 201});

    // if changing scene, return
    if (m_SceneManager.IsChangingScene()) {
        LOG_DEBUG("Changing Scene");
        return;
    }

    m_Rockman->DoBehavior(m_ForeObjectTileBox);

    glm::vec2 RockmanPos = m_Rockman->GetPosition();
    int SceneStage = m_SceneManager.GetCurrentScene();

    m_EnemyManager.Update(CameraPos,RockmanPos,SceneStage);
    ReloadMagazine(app);

    if(!CheckIfRockmanInMap(CameraPos,RockmanPos,glm::vec2{50,50}) &&
        m_Rockman->GetCurrentState() == Rockman::LiveState::Normal){
        //Let Rockman Die.
        m_Rockman->SetLifeState(Rockman::LiveState::Death);
    }
    m_Testbox->Move();
    if (Util::Input::IsKeyPressed(Util::Keycode::Q)) {
        LOG_INFO("Testbox Position");
        LOG_INFO(std::to_string(m_Testbox->GetPosition().x) + " " +
                 std::to_string(m_Testbox->GetPosition().y));
    }
    /*
    LOG_INFO("Camera Position");
    LOG_INFO(std::to_string(app->GetCameraPosition().x)+"
    "+std::to_string(app->GetCameraPosition().y)); LOG_INFO("Rockman Position");
    LOG_INFO(std::to_string(m_Rockman->GetPosition().x)+"
    "+std::to_string(m_Rockman->GetPosition().y)); LOG_INFO("Root Size");
    LOG_INFO(std::to_string(app->GetRoot()->size()));
    LOG_INFO("Bombombomb Position");
    LOG_INFO(std::to_string(m_Bombombomb[0]->GetPosition().x)+"
    "+std::to_string(m_Bombombomb[0]->GetPosition().y));
    */
    if (Util::Input::IsKeyPressed(Util::Keycode::B)) {
        m_Rockman->SetPosition(CameraPos);
        m_Testbox->SetPosition(CameraPos);
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::L)) {
        m_Rockman->SetPosition({7962,-2000});
        m_Testbox->SetPosition({7962,-2000});
    }
    if(Util::Input::IsKeyPressed(Util::Keycode::G)){
        m_Rockman->SetLifeState(Rockman::LiveState::Normal);
    }
    // m_Rockman->SetPosition({360,-3408});
    //  TODO : change this to win
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
        magazine = m_Screwdriver[i]->GetAmmo();
        for (auto Ammo : magazine) {
            m_Magazine.push(Ammo);
            app->GetRoot()->AddChild(Ammo->GetChild());
        }
    }
    for (int i = 0; i < 1; i++) { // SniperJoe Ammo
        magazine = m_SniperJoe->GetAmmo();
        for (auto Ammo : magazine) {
            m_Magazine.push(Ammo);
            app->GetRoot()->AddChild(Ammo->GetChild());
        }
    }
    magazine = m_Mambu->GetAmmo();
    for (auto Ammo : magazine) {
        m_Magazine.push(Ammo);
        app->GetRoot()->AddChild(Ammo->GetChild());
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
bool PhaseStage::CheckIfRockmanInMap(glm::vec2 cameraposition,glm::vec2 position,glm::vec2 offset) {
    float LeftX = cameraposition.x-384-offset.x,RightX = cameraposition.x+384+offset.x;
    float BottomY = cameraposition.y-360-offset.y,TopY = cameraposition.y+360+offset.y;
    return (LeftX <= position.x && position.x <= RightX) && (BottomY <= position.y && position.y <= TopY);
}
