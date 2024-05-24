#ifndef COLLIDE_EVENT_MANAGER_HPP
#define COLLIDE_EVENT_MANAGER_HPP

#include "EnemyAttribute.hpp"
#include "Item.hpp"
#include "Rockman.hpp"
#include "Scorebar.hpp"
#include <memory>
#include <utility>

class PhaseStage;

// TODO : add item collide event in future
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

    void SetScorebar(std::shared_ptr<Scorebar> scorebar) {
        m_Scorebar = std::move(scorebar);
    }

private:
    std::shared_ptr<Rockman> m_Rockman;
    std::shared_ptr<std::queue<std::shared_ptr<Ammo>>> m_Magazine;
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::shared_ptr<std::queue<std::shared_ptr<Item>>> m_Items;
    std::shared_ptr<Scorebar> m_Scorebar;
};

#endif
