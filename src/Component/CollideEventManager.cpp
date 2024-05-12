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
        if(ammo->GetAmmoType() != AmmoType::ENEMY)
            continue;
        for(auto & j : rockmanCollider) {
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
    // waiting for implementation of item

    // 5. item <---> enemy
    // waiting for implementation of item
}
