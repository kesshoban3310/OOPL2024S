#ifndef PHASE_STAGE_HPP
#define PHASE_STAGE_HPP

#include "Component/Phase.hpp"
#include "Component/SceneManager.hpp"
#include "Component/TileMap.hpp"
#include "Component/Blaster.hpp"
#include "Component/ScrewDriver.hpp"
#include "IncludeComponent.hpp"

class PhaseStage final : public Phase {
public:
    void Init(App *app) override;

    void Update(App *app) override;

    void Leave(App *app) override;

    explicit PhaseStage(App::State lastState)
        : Phase(lastState){};

private:
    std::shared_ptr<Backgroundmap> m_BackgroundObjects;
    std::shared_ptr<Backgroundmap> m_ForegroundObjects;
    std::shared_ptr<Rockman> m_Rockman;
    std::shared_ptr<Scorebar> m_Scorebar;
    std::shared_ptr<TestBox> m_Testbox;
    std::queue<std::shared_ptr<Ammo>> m_Magazine; //Store Rockman's Ammo.
    std::vector<std::shared_ptr<Blaster>> m_Blaster;
    std::vector<std::shared_ptr<Screwdriver>> m_Screwdriver;
    SceneManager m_SceneManager;

    void ReloadMagazine(App *app); //Update Every Ammo In The Stage.
};

#endif // PHASE_STAGE_HPP
