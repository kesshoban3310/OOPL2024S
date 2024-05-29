#include "PhaseStage.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"
#include "algorithm"
#include "limits"

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
        app->GetRoot()->AddChild(octopusbattery->GetChild());
    }

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

    // Set the collide event manager
    m_CollideEventManager.SetRockman(m_Rockman);
    m_CollideEventManager.SetMagazine(m_Magazine);
    m_CollideEventManager.SetItems(m_Items);
    m_CollideEventManager.SetScorebar(m_Scorebar);

    // Add the root
    m_Rockman->DoBehavior(*m_ForeObjectTileBox);
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

    // get some info
    glm::vec2 CameraPos = app->GetCameraPosition();

    // set healthbar and scorebar
    m_Scorebar->Show(CameraPos);
    m_RockmanHealthBar->SetPosition(
        glm::vec2{CameraPos.x - 311, CameraPos.y + 201});
    m_RockmanHealthBar->SetVisable(std::max(m_Rockman->GetHealth(), 0));

    // if changing scene, return
    if (m_SceneManager.IsChangingScene()) {
        LOG_DEBUG("Changing Scene");
        return;
    }

    m_Rockman->DoBehavior(*m_ForeObjectTileBox);
    for (int i = 0; i < 4; i++) {
        m_Blaster[i]->DoBehavior(m_Rockman->GetPosition());
    }
    for (int i = 0; i < 4; i++) {
        m_Bombombomb[i]->DoBehavior(CameraPos);
    }
    for (int i = 0; i < 3; i++) {
        m_Screwdriver[i]->DoBehavior(m_Rockman->GetPosition());
    }

    for (int i = 0; i < 8; i++) {
        m_OctopusBattery[i]->DoBehavior(CameraPos);
    }

    m_CollideEventManager.Update();
    ReloadMagazine(app);
    // m_Testbox->Move();

    /*
    LOG_INFO("Camera Position");
    LOG_INFO(std::to_string(app->GetCameraPosition().x)+"
    "+std::to_string(app->GetCameraPosition().y)); LOG_INFO("Rockman Position");
    LOG_INFO(std::to_string(m_Rockman->Getposition().x)+"
    "+std::to_string(m_Rockman->Getposition().y)); LOG_INFO("Root Size");
    LOG_INFO(std::to_string(app->GetRoot()->size()));
    LOG_INFO("Bombombomb Position");
    LOG_INFO(std::to_string(m_Bombombomb[0]->GetPosition().x)+"
    "+std::to_string(m_Bombombomb[0]->GetPosition().y));
    */
    if (Util::Input::IsKeyPressed(Util::Keycode::B))
        m_Rockman->SetPosition(app->GetCameraPosition());
    if (Util::Input::IsKeyPressed(Util::Keycode::L)) {
        m_Rockman->SetPosition({12638, -398});
        m_Testbox->SetPosition({12638, -398});
    }

    UpdateItems(app);

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
    int magazine_size = m_Magazine->size();
    for (int i = 0; i < magazine_size; i++) {
        auto Ammo = m_Magazine->front();
        m_Magazine->pop();
        Ammo->Behavior();
        if (Ammo->Outofrange(CameraPosition) || Ammo->IsMarkedForRemoval()) {
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
