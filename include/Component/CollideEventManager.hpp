#ifndef COLLIDE_EVENT_MANAGER_HPP
#define COLLIDE_EVENT_MANAGER_HPP

#include "Component/Bomb.hpp"
#include "EnemyAttribute.hpp"
#include "Item.hpp"
#include "Rockman.hpp"
#include "Scorebar.hpp"
#include "Util/Renderer.hpp"
#include "Util/SFX.hpp"
#include <memory>
#include <random>
#include <utility>

class PhaseStage;

class CollideEventManager {
public:
    CollideEventManager() = default;
    ~CollideEventManager() = default;

    void Update();

    void SetRockman(std::shared_ptr<Rockman> rockman) {
        m_Rockman = std::move(rockman);
    }

    void
    SetMagazine(std::shared_ptr<std::queue<std::shared_ptr<Ammo>>> magazine) {
        m_Magazine = std::move(magazine);
    }

    void SetEnemies(std::vector<std::shared_ptr<Enemy>> enemies) {
        m_Enemies = std::move(enemies);
    }

    void SetItems(std::shared_ptr<std::queue<std::shared_ptr<Item>>> items) {
        m_Items = std::move(items);
    }

    void SetBombs(std::shared_ptr<std::queue<std::shared_ptr<Bomb>>> bombs) {
        m_Bombs = std::move(bombs);
    }

    void SetScorebar(std::shared_ptr<Scorebar> scorebar) {
        m_Scorebar = std::move(scorebar);
    }

    void SetRenderer(std::shared_ptr<Util::Renderer> renderer) {
        m_Renderer = std::move(renderer);
    }

    void SetApp(App *app) { m_App = app; }

    void SetIsStageEnded(std::shared_ptr<bool> isStageEnded) {
        m_IsStageEnded = std::move(isStageEnded);
    }

private:
    std::shared_ptr<Rockman> m_Rockman;
    std::shared_ptr<std::queue<std::shared_ptr<Ammo>>> m_Magazine;
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::shared_ptr<std::queue<std::shared_ptr<Item>>> m_Items;
    std::shared_ptr<std::queue<std::shared_ptr<Bomb>>> m_Bombs;
    std::shared_ptr<Scorebar> m_Scorebar;
    std::shared_ptr<Util::Renderer> m_Renderer;
    App *m_App;
    std::shared_ptr<bool> m_IsStageEnded;
    std::mt19937 gen = std::mt19937(std::random_device{}());
    std::uniform_real_distribution<> dis =
        std::uniform_real_distribution<>(0, 1);
    std::shared_ptr<Util::SFX> m_DamageSoundRockman = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sound/RockmanDamage.mp3");
    std::shared_ptr<Util::SFX> m_DamageSoundEnemy = std::make_shared<Util::SFX>(RESOURCE_DIR"/Sound/EnemyDamage.mp3");
};

#endif