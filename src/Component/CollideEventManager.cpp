#include "Component/CollideEventManager.hpp"
#include "Component/Item.hpp"
#include "Component/App.hpp"
#include <random>

void CollideEventManager::Update() {
    auto RockmanGetDamage = [this](int damage) {
        if (m_Rockman->GetInvincible())
            return;
        m_Rockman->SetHealth(std::max(0, m_Rockman->GetHealth() - damage));
        m_Rockman->SetInvincible();
    };

    auto EnemyGetDamage = [this](const std::shared_ptr<Enemy> &enemy,
                                 int damage) {
        if (enemy->GetHurtState() == Enemy::HurtState::INVINCIBLE ||
            enemy->GetLifeState() == Enemy::LifeState::DEAD)
            return;
        enemy->SetHealth(enemy->GetHealth() - damage);
        if (enemy->GetHealth() <= 0) {
            ItemType type = ItemType::SMALL_HEALTH_ENERGY;
            double rng = dis(gen);

            if (rng < 0.5) {
                return;
            }
            else if (rng < 0.79) {
                type = ItemType::SCORE_BALL;
            }
            else if (rng < 0.84) {
                type = ItemType::SMALL_HEALTH_ENERGY;
            }
            else if (rng < 0.89) {
                type = ItemType::SMALL_WEAPON_ENERGY;
            }
            else if (rng < 0.94) {
                type = ItemType::BIG_HEALTH_ENERGY;
            }
            else if (rng < 0.99) {
                type = ItemType::BIG_WEAPON_ENERGY;
            }
            else {
                type = ItemType::ONE_UP;
            }

            auto item = std::make_shared<Item>(type, enemy->GetPosition() +
                                                         glm::vec2(0, 40));
            m_Items->push(item);
            m_Renderer->AddChild(item);
        }
    };

    // 1. rockman <---> ammo : completed
    int ammoCount = (int)m_Magazine->size();
    for (int i = 0; i < ammoCount; i++) {
        std::shared_ptr<Ammo> ammo = m_Magazine->front();
        m_Magazine->pop();
        m_Magazine->push(ammo);
        auto rockmanCollider = m_Rockman->GetCollider();
        auto ammoCollider = ammo->GetCollider();
        if (ammo->GetAmmoType() != AmmoType::ENEMY)
            continue;
        for (auto &j : rockmanCollider) {
            if (IsColliding(*j, ammoCollider)) {
                RockmanGetDamage(2);
                ammo->MarkForRemoval();
                break;
            }
        }
    }

    // 2. rockman <---> enemy
    for (auto &enemy : m_Enemies) {
        auto rockmanCollider = m_Rockman->GetCollider();
        auto enemyCollider = enemy->GetCollider();
        if (enemy->GetLifeState() == Enemy::LifeState::DEAD)
            continue;
        for (auto &j : rockmanCollider) {
            if (IsColliding(*j, enemyCollider)) {
                RockmanGetDamage(1);
                break;
            }
        }
    }

    // 3. ammo <---> enemy
    ammoCount = (int)m_Magazine->size();
    for (int i = 0; i < ammoCount; i++) {
        std::shared_ptr<Ammo> ammo = m_Magazine->front();
        m_Magazine->pop();
        m_Magazine->push(ammo);
        for (auto &enemy : m_Enemies) {
            auto enemyCollider = enemy->GetCollider();
            auto ammoCollider = ammo->GetCollider();
            if (ammo->GetAmmoType() != AmmoType::ROCKMAN)
                continue;
            if (IsColliding(enemyCollider, ammoCollider) &&
                enemy->GetLifeState() != Enemy::LifeState::DEAD) {
                EnemyGetDamage(enemy, 2);
                ammo->MarkForRemoval();
                break;
            }
        }
    }

    // 4. item <---> rockman
    // TODO : make more implementation to other items
    int itemCount = (int)m_Items->size();
    for (int i = 0; i < itemCount; i++) {
        auto item = m_Items->front();
        m_Items->pop();
        m_Items->push(item);
        auto rockmanCollider = m_Rockman->GetCollider();
        auto itemCollider = item->GetCollider();
        for (auto &j : rockmanCollider) {
            if (IsColliding(*j, itemCollider)) {
                item->MarkForRemoval();
                switch (item->GetType()) {
                case ItemType::SMALL_HEALTH_ENERGY:
                    m_Rockman->SetHealth(
                        std::min(28, m_Rockman->GetHealth() + 2));
                    break;
                case ItemType::BIG_HEALTH_ENERGY:
                    m_Rockman->SetHealth(
                        std::min(28, m_Rockman->GetHealth() + 4));
                    break;
                case ItemType::SMALL_WEAPON_ENERGY:
                    break;
                case ItemType::BIG_WEAPON_ENERGY:
                    break;
                case ItemType::ONE_UP:
                    m_App->SetLifeCount(std::min(99u, m_App->GetLifeCount() + 1));
                    break;
                case ItemType::SPECIAL_WEAPON_ITEM:
                    *m_IsStageEnded = true;
                    break;
                case ItemType::SCORE_BALL:
                    m_Scorebar->AddScore(1000);
                    break;
                }
                break;
            }
        }
    }

    // 5. rockman <---> bomb
    int bombCount = (int)m_Bombs->size();
    for (int i = 0; i < bombCount; i++) {
        std::shared_ptr<Bomb> bomb = m_Bombs->front();
        m_Bombs->pop();
        m_Bombs->push(bomb);
        auto rockmanCollider = m_Rockman->GetCollider();
        auto bombCollider = bomb->GetCollider();
        for (auto &j : rockmanCollider) {
            if (IsColliding(*j, bombCollider)) {
                if(bomb->GetState() == Bomb::State::FALLING)
                    bomb->SetToExplode();
                RockmanGetDamage(3);
                break;
            }
        }
    }
}
