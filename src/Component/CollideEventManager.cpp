#include "Component/CollideEventManager.hpp"

void CollideEventManager::Update() {
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
                m_Rockman->SetHealth(m_Rockman->GetHealth() - 2);
                ammo->MarkForRemoval();
                break;
            }
        }
    }

    // 2. rockman <---> enemy
    for (auto &enemy : m_Enemies) {
        // waiting for GetCollider of enemy
    }

    // 3. ammo <---> enemy
    // waiting for GetCollider of enemy
    ammoCount = (int)m_Magazine->size();
    for (int i = 0; i < ammoCount; i++) {
        std::shared_ptr<Ammo> ammo = m_Magazine->front();
        m_Magazine->pop();
        m_Magazine->push(ammo);
    }

    // 4. item <---> rockman
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
                        std::max(28, m_Rockman->GetHealth() + 2));
                    break;
                case ItemType::BIG_HEALTH_ENERGY:
                    m_Rockman->SetHealth(
                        std::max(28, m_Rockman->GetHealth() + 4));
                    break;
                case ItemType::SMALL_WEAPON_ENERGY:
                    break;
                case ItemType::BIG_WEAPON_ENERGY:
                    break;
                case ItemType::ONE_UP:
                    break;
                case ItemType::SPECIAL_WEAPON_ITEM:
                    break;
                case ItemType::SCORE_BALL:
                    m_Scorebar->AddScore(1000);
                    break;
                }
                break;
            }
        }
    }

    // 5. item <---> enemy
    // waiting for implementation of item
}
