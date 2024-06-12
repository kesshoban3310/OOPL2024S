#include "PhaseStage.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"
#include "algorithm"
#include "limits"

void PhaseStage::Init(App *app) {
    m_IsWaitingForEndAnimation = std::make_shared<bool>(false);

    // define enemy array
    std::vector<std::shared_ptr<Enemy>> enemies;

    // Load the map
    m_BackgroundObjects = std::make_shared<Backgroundmap>("Bomb Man Stage");
    m_ForegroundObjects = std::make_shared<Backgroundmap>("Bomb Man Stage");

    // Load Rockman
    m_Rockman = std::make_shared<Rockman>(glm::vec2{360, -2688},
                                          Rockman::LiveState::Initial);
    // Load Word Ready
    std::string Word = "ready";
    m_WordReady = std::make_shared<Words>(Word, glm::vec2{3, 3});
    for (int i = 0; i < Word.size(); i++) {
        m_WordReady->SetPosition(i, glm::vec2{332 + 24 * i, -3349});
    }

    // Load Word End
    m_WordForEndAnimation =
        std::make_shared<Words>("stageclear", glm::vec2{3, 3});
    for (int i = 0; i < 5; i++) {
        m_WordForEndAnimation->SetPosition(i, glm::vec2{12600 + 24 * i, -2500});
    }
    for (int i = 5; i < 10; i++) {
        m_WordForEndAnimation->SetPosition(i, glm::vec2{12600 + 24 * (i - 5), -2550});
    }

    // Load Rockman Healthbar
    m_RockmanHealthBar =
        std::make_shared<HealthBar>(glm::vec2{360 - 311, -3408 + 201},
                                    "/Picture/Character/Health/blood", 29);
    // Load Boss Healthbar
    m_BossHealthBar =
        std::make_shared<HealthBar>(glm::vec2{360 - 311 + 48, -3408 + 201},
                                    "/Picture/Boss/Bombman/health/blood", 29);

    // Load Scorebar
    m_Scorebar = std::make_shared<Scorebar>(glm::vec2{360, -3408});
    // Load Testbox
    m_Testbox =
        std::make_shared<TestBox>(glm::vec2{360, -3408}, glm::vec2{3, 3});
    // Load Map
    m_BackgroundObjects->SetImagetoBackgroundObject();
    m_ForegroundObjects->SetImagetoForegroundObject();
    m_ForeObjectTileBox =
        std::make_shared<std::vector<std::shared_ptr<TileBox>>>(
            m_ForegroundObjects->GetTileBox());
    // Load Magazine
    m_Magazine = std::make_shared<std::queue<std::shared_ptr<Ammo>>>();

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
    for (int i = 0; i < 5; i++) {
        std::shared_ptr<Kamadoma> kamadoma = std::make_shared<Kamadoma>(
            KamadomaPath, KamadomaPoints, KamadomaPoints[3 + i], 3 + i,
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
                glm::vec2{12 * 3, 12 * 3}, glm::vec2{16, 0}, glm::vec2{3, 3},
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
                glm::vec2{12 * 3, 12 * 3}, glm::vec2{16, 0}, glm::vec2{3, 3},
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
    std::vector<std::pair<glm::vec2, glm::vec2>> GabyollPos;
    GabyollPos = {
        {glm::vec2{8108, -1888}, glm::vec2{8260, -1888}},
        {glm::vec2{8534, -1744}, glm::vec2{8598, -1744}},
        {glm::vec2{8936, -2080}, glm::vec2{7962, -2080}},
    };
    for (int i = 0; i < 3; i++) {
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
    // setting items
    m_Items = std::make_shared<std::queue<std::shared_ptr<Item>>>();
    std::vector<std::pair<ItemType, glm::vec2>> itemsAttributes = {
        {ItemType::SMALL_HEALTH_ENERGY, {4704, -3270}},
        {ItemType::SMALL_HEALTH_ENERGY, {4748, -3270}},
        {ItemType::BIG_WEAPON_ENERGY, {5176, -3540}},
        {ItemType::BIG_HEALTH_ENERGY, {5176, -2830}},
        {ItemType::ONE_UP, {10718, -328}}};
    for (auto itemAttribute : itemsAttributes) {
        std::shared_ptr<Item> item =
            std::make_shared<Item>(itemAttribute.first, itemAttribute.second,
                                   std::numeric_limits<float>::infinity());
        m_Items->push(item);
        app->GetRoot()->AddChild(item);
    }

    // setting bomb
    m_Bombs = std::make_shared<std::queue<std::shared_ptr<Bomb>>>();

    // Boss
    m_Boss = std::make_shared<Boss>(m_Bombs, m_Items, app->GetRoot());
    m_Enemies.push_back(m_Boss);
    app->GetRoot()->AddChild(m_Boss->GetChild());

    // Set the collide event manager
    m_CollideEventManager.SetRockman(m_Rockman);
    m_CollideEventManager.SetMagazine(m_Magazine);
    m_CollideEventManager.SetItems(m_Items);
    m_CollideEventManager.SetBombs(m_Bombs);
    m_CollideEventManager.SetScorebar(m_Scorebar);
    m_CollideEventManager.SetEnemies(m_Enemies);
    m_CollideEventManager.SetRenderer(app->GetRoot());
    m_CollideEventManager.SetApp(app);
    m_CollideEventManager.SetIsStageEnded(m_IsWaitingForEndAnimation);

    // Add the root
    m_Rockman->DoBehavior(*m_ForeObjectTileBox);
    m_Scorebar->Show({360, -3408});
    app->GetRoot()->AddChild(m_Testbox->Getchild());
    app->GetRoot()->AddChildren(m_BackgroundObjects->GetChildren());
    app->GetRoot()->AddChildren(m_ForegroundObjects->GetChildren());
    app->GetRoot()->AddChildren(m_Rockman->GetAllChildren());
    app->GetRoot()->AddChildren(m_Scorebar->GetChildren());
    app->GetRoot()->AddChild(m_KillerBomb->GetChild());
    app->GetRoot()->AddChild(m_SniperJoe->GetChild());
    app->GetRoot()->AddChild(m_RockmanHealthBar->GetChild());
    app->GetRoot()->AddChild(m_BossHealthBar->GetChild());
    app->GetRoot()->AddChildren(m_WordReady->GetChildren());
    app->GetRoot()->AddChildren(m_WordForEndAnimation->GetChildren());
    app->GetRoot()->AddChildren(app->GetDebugModeWords()->GetChildren());

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

    // setting person life
    m_PersonLife = std::make_shared<PersonLife>();
    app->GetRoot()->AddChild(m_PersonLife);
    m_EnemyManager.SetEnemies(m_Enemies);
    app->GetRoot()->Update();
}

void PhaseStage::Update(App *app) {
    // update SceneManager
    m_SceneManager.Update(m_Rockman->GetPosition());
    app->SetCameraPosition(m_SceneManager.GetCameraPosition());

    // get some info
    glm::vec2 CameraPos = app->GetCameraPosition();

    // set healthbar and scorebar and person life ui
    m_Scorebar->Show(CameraPos);
    m_RockmanHealthBar->SetPosition(
        glm::vec2{CameraPos.x - 311, CameraPos.y + 201});
    m_RockmanHealthBar->SetVisable(std::max(m_Rockman->GetHealth(), 0));
    m_BossHealthBar->SetPosition(
        glm::vec2{CameraPos.x - 311 + 48, CameraPos.y + 201});
    m_BossHealthBar->SetVisable(std::max(m_Boss->GetHealth(), 0),
                                m_Boss->IsTriggered() &&
                                    m_Boss->GetLifeState() ==
                                        Enemy::LifeState::LIFE);
    m_PersonLife->Update(app->GetLifeCount(), CameraPos);

    // If Rockman Dead,then Rivival it.
    if (m_Rockman->GetCurrentState() == Rockman::LiveState::WAITREVIVAL) {
        RockmanRivival(app);
        return;
    }
    // Ready Animation.
    if (m_Rockman->GetCurrentState() == Rockman::LiveState::WaitSpawn) {
        StartAnimation(app);
        return;
    }

    // if changing scene, return
    if (m_SceneManager.IsChangingScene()) {
        LOG_DEBUG("Changing Scene");
        return;
    }
    m_Rockman->DoBehavior(*m_ForeObjectTileBox);

    glm::vec2 RockmanPos = m_Rockman->GetPosition();
    int SceneStage = m_SceneManager.GetCurrentScene();

    m_EnemyManager.Update(CameraPos, RockmanPos, SceneStage);

    m_CollideEventManager.Update();
    ReloadMagazine(app);
    // m_Testbox->Move();

    if (!CheckIfRockmanInMap(CameraPos, RockmanPos, glm::vec2{50, 50}) &&
        m_Rockman->GetCurrentState() == Rockman::LiveState::Normal) {
        // Let Rockman Die.
        m_Rockman->SetLifeState(Rockman::LiveState::Death);
    }

    if (Util::Input::IsKeyDown(Util::Keycode::NUM_8)) {
        SetDebugMode(app);
    }
    if (app->GetDebugModeState()) {
        app->SetDebugModeMessagePosition(app->GetCameraPosition());
        DebugMode(app);
    }

    /*
    LOG_INFO("Camera Position");
    LOG_INFO(std::to_string(app->GetCameraPosition().x)+"
    "+std::to_string(app->GetCameraPosition().y)); LOG_INFO("Rockman Position");
    LOG_INFO(std::to_string(m_Rockman->Getposition().x)+"
    "+std::to_string(m_Rockman->Getposition().y)); LOG_INFO("Root Size");
    LOG_INFO(std::to_string(app->GetRoot()->size()));
    */
    if (Util::Input::IsKeyPressed(Util::Keycode::B))
        m_Rockman->SetPosition(app->GetCameraPosition());
    if (Util::Input::IsKeyPressed(Util::Keycode::L)) {
        m_Rockman->SetPosition({12638, -398});
        m_Testbox->SetPosition({12638, -398});
    }

    // update items and bombs
    UpdateItems(app);
    UpdateBombs(app);

    // TODO : change this to win
    if (Util::Input::IsKeyUp(Util::Keycode::I)) {
        app->ChangeState(App::State::ENDING_ANIMATION);
        return;
    }

    if (m_IsPlayingEndAnimation) {
        m_WordForEndAnimation->ShowAll();
    }

    if (Util::Time::GetElapsedTimeMs() >= m_EndTimeStampOfEndAnimation) {
        app->ChangeState(App::State::ENDING_ANIMATION);
        return;
    }

    if (*m_IsWaitingForEndAnimation) {
        *m_IsWaitingForEndAnimation = false;
        m_IsPlayingEndAnimation = true;
        m_EndTimeStampOfEndAnimation = Util::Time::GetElapsedTimeMs() + 4000;
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
        m_Magazine->push(Ammo);
        app->GetRoot()->AddChild(Ammo->GetChild());
    }
    for (int i = 0; i < 4; i++) { // Blaster Magazine
        magazine = m_Blaster[i]->Getammo();
        for (auto Ammo : magazine) {
            m_Magazine->push(Ammo);
            app->GetRoot()->AddChild(Ammo->GetChild());
        }
    }
    for (int i = 0; i < 3; i++) { // Screwdriver Magazine
        magazine = m_Screwdriver[i]->GetAmmo();
        for (auto Ammo : magazine) {
            m_Magazine->push(Ammo);
            app->GetRoot()->AddChild(Ammo->GetChild());
        }
    }
    for (int i = 0; i < 1; i++) { // SniperJoe Ammo
        magazine = m_SniperJoe->GetAmmo();
        for (auto Ammo : magazine) {
            m_Magazine->push(Ammo);
            app->GetRoot()->AddChild(Ammo->GetChild());
        }
    }
    magazine = m_Mambu->GetAmmo();
    for (auto Ammo : magazine) {
        m_Magazine->push(Ammo);
        app->GetRoot()->AddChild(Ammo->GetChild());
    }
    int magazine_size = m_Magazine->size();
    for (int i = 0; i < magazine_size; i++) {
        auto Ammo = m_Magazine->front();
        m_Magazine->pop();
        Ammo->Behavior();
        if (Ammo->Outofrange(CameraPosition)) {
            app->GetRoot()->RemoveChild(Ammo->GetChild());
            continue;
        }
        m_Magazine->push(Ammo);
    }
}

void PhaseStage::UpdateItems(App *app) {
    int itemSize = (int)m_Items->size();
    for (int i = 0; i < itemSize; i++) {
        auto item = m_Items->front();
        m_Items->pop();
        item->Update(m_ForeObjectTileBox);
        if (!item->IsAlive()) {
            app->GetRoot()->RemoveChild(item);
            continue;
        }
        m_Items->push(item);
    }
}

void PhaseStage::UpdateBombs(App *app) {
    for(int i=0;i<4;i++){
        auto Bombombomb = m_Bombombomb[i]->GetBombs();
        for(int i=0;i<Bombombomb.size();i++) {
            m_Bombs->push(Bombombomb[i]);
            app->GetRoot()->AddChild(Bombombomb[i]);
        }
    }
    int bombSize = (int)m_Bombs->size();
    for (int i = 0; i < bombSize; i++) {
        auto bomb = m_Bombs->front();
        m_Bombs->pop();
        bomb->Update(m_ForeObjectTileBox);
        if (!bomb->IsAlive() ||
            m_SceneManager.IsFallOutOfScene(bomb->GetPosition())) {
            app->GetRoot()->RemoveChild(bomb);
            continue;
        }
        m_Bombs->push(bomb);
    }
}

bool PhaseStage::CheckIfRockmanInMap(glm::vec2 cameraposition,
                                     glm::vec2 position, glm::vec2 offset) {
    float LeftX = cameraposition.x - 384 - offset.x,
          RightX = cameraposition.x + 384 + offset.x;
    float BottomY = cameraposition.y - 360 - offset.y,
          TopY = cameraposition.y + 360 + offset.y;
    return (LeftX <= position.x && position.x <= RightX) &&
           (BottomY <= position.y && position.y <= TopY);
}
void PhaseStage::RockmanRivival(App *app) {
    glm::vec2 NowPos = m_Rockman->GetPosition();
    int NowScene = m_SceneManager.GetCurrentScene();
    if((NowPos.x >= 11547 && NowScene == 4) || NowScene > 5) {
        NowScene = 5;
    }
    m_Rockman->SetPosition(RockmanRevivalPosition[std::max(0, NowScene)]);
    m_EnemyManager.Reset();
    m_SceneManager.Update(m_Rockman->GetPosition());
    app->SetCameraPosition(m_SceneManager.GetCameraPosition());
    m_Rockman->Revival();
}
void PhaseStage::StartAnimation(App *app) {
    if (StartTimer == 0) {
        StartTimer = Util::Time::GetElapsedTimeMs();
        m_WordReady->ShowAll();
    }
    else if (Util::Time::GetElapsedTimeMs() - StartTimer > StartTime) {
        m_WordReady->DisableAll();
        m_Rockman->SetLifeState(Rockman::LiveState::Spawn);
        StartTimer = 0;
    }
}
void PhaseStage::SetDebugMode(App *app) {
    std::shared_ptr<Words> DebugWord = app->GetDebugModeWords();
    std::string DebugMessage;
    if(app->GetDebugModeState() == true){
        app->SetDebugModeState(false);
        app->GetDebugModeWords()->DisableAll();
        m_Rockman->SetRockmanDebugMode();
    }
    else{
        RockmanRestHealth = m_Rockman->GetHealth();
        PersonRestLife = app->GetLifeCount();
        m_Rockman->SetRockmanDebugMode();
        app->SetDebugModeState(true);
        app->GetDebugModeWords()->ShowAll();
    }
}
void PhaseStage::DebugMode(App *app) {
    m_Rockman->SetHealth(RockmanRestHealth);
    app->SetLifeCount(PersonRestLife);
    int SceneNum = -1;
    if (Util::Input::IsKeyDown(Util::Keycode::NUM_1)) {
        SceneNum = 0;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::NUM_2)) {
        SceneNum = 1;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::NUM_3)) {
        SceneNum = 2;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::NUM_4)) {
        SceneNum = 3;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::NUM_5)) {
        SceneNum = 4;
    }
    else if (Util::Input::IsKeyDown(Util::Keycode::NUM_6)) {
        SceneNum = 5;
    }
    if (SceneNum != -1) {
        m_Rockman->SetPosition(RockmanRevivalPosition[std::max(0, SceneNum)]);
        app->SetCameraPosition(m_SceneManager.GetCameraPosition());
    }
}
