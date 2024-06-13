#ifndef PHASE_STAGE_HPP
#define PHASE_STAGE_HPP

#include "Component/Blaster.hpp"
#include "Component/Bomb.hpp"
#include "Component/Bombombomb.hpp"
#include "Component/CollideEventManager.hpp"
#include "Component/HealthBar.hpp"
#include "Component/OctopusBattery.hpp"
#include "Component/Phase.hpp"
#include "Component/SceneManager.hpp"
#include "Component/ScrewDriver.hpp"
#include "Component/TileMap.hpp"
#include "Component/PersonLife.hpp"
#include "Component/OctopusBattery.hpp"
#include "Component/KillerBomb.hpp"
#include "Component/Mambu.hpp"
#include "Component/Gabyoll.hpp"
#include "Component/SniperJoe.hpp"
#include "Component/Kamadoma.hpp"
#include "Component/EnemyManager.hpp"
#include "Component/Words.hpp"
#include "Component/Boss.hpp"
#include "IncludeComponent.hpp"
#include "Util/BGM.hpp"

class PhaseStage final : public Phase {
public:
    void Init(App *app) override;

    void Update(App *app) override;

    void Leave(App *app) override;

    explicit PhaseStage(App::State lastState)
        : Phase(lastState){};

private:
    std::shared_ptr<bool> m_IsWaitingForEndAnimation;
    std::shared_ptr<Backgroundmap> m_BackgroundObjects;
    std::shared_ptr<Backgroundmap> m_ForegroundObjects;
    std::shared_ptr<Rockman> m_Rockman;
    std::shared_ptr<KillerBomb> m_KillerBomb;
    std::shared_ptr<TestBox> m_Testbox;
    std::shared_ptr<Mambu> m_Mambu;
    std::shared_ptr<SniperJoe> m_SniperJoe;
    std::shared_ptr<Scorebar> m_Scorebar;
    std::shared_ptr<HealthBar> m_RockmanHealthBar, m_BossHealthBar;
    std::shared_ptr<Words> m_WordReady; //Words Ready.
    std::shared_ptr<std::queue<std::shared_ptr<Ammo>>> m_Magazine; // Store Rockman's Ammo.
    std::vector<std::shared_ptr<Blaster>> m_Blaster;
    std::vector<std::shared_ptr<Kamadoma>> m_Kamadoma;
    std::vector<std::shared_ptr<Gabyoll>> m_Gabyoll;
    std::vector<std::shared_ptr<Screwdriver>> m_Screwdriver;
    std::vector<std::shared_ptr<OctopusBattery>> m_OctopusBattery;
    std::vector<std::shared_ptr<Bombombomb>> m_Bombombomb;
    std::shared_ptr<Boss> m_Boss;
    std::shared_ptr<std::queue<std::shared_ptr<Item>>> m_Items;
    SceneManager m_SceneManager;
    EnemyManager m_EnemyManager;
    CollideEventManager m_CollideEventManager;
    std::shared_ptr<std::vector<std::shared_ptr<TileBox>>> m_ForeObjectTileBox;
    std::shared_ptr<std::queue<std::shared_ptr<Bomb>>> m_Bombs;
    std::shared_ptr<PersonLife> m_PersonLife;
    std::shared_ptr<Util::BGM> m_BGM;


    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    void ReloadMagazine(App *app); // Update Every Ammo In The Stage.
    void UpdateItems(App *app);
    void UpdateBombs(App *app);
    bool CheckIfRockmanInMap(glm::vec2 cameraposition,glm::vec2 position,glm::vec2 offset);

    //Rockman's Rivival Place.
    std::unordered_map<int,glm::vec2> RockmanRevivalPosition = {
        {0, {258, -3056}},
        {1, {5080, -2284}},
        {2, {4837, -1522}},
        {3, {8808, -774}},
        {4, {9291, -3}},
        {5, {12041, -13}},
    };
    //Rockman Rivival Setting.
    void RockmanRivival(App *app);
    //Start Animation For Start.
    long long StartTimer = 0,StartTime = 3000;
    void StartAnimation(App *app);

    std::shared_ptr<Words> m_WordForEndAnimation;
    bool m_IsPlayingEndAnimation = false;
    float m_EndTimeStampOfEndAnimation = std::numeric_limits<float>::infinity();

    //Debug Mode On;
    void SetDebugMode(App *app);
    unsigned int RockmanRestHealth,PersonRestLife;
    void DebugMode(App *app);

};

#endif // PHASE_STAGE_HPP
