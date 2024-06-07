//
// Created by User on 2024/5/31.
//

#include "Component/EnemyManager.hpp"

EnemyManager::EnemyManager() {}

void EnemyManager::Update(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                          int SceneStage) {
    int N = m_Enemies.size();
    for (int i = 0; i < N; i++) {
        if (m_Enemies[i]->GetLifeState() == Enemy::LifeState::DEAD) {
            m_Enemies[i]->Revival();
        }
        else {
            m_Enemies[i]->DoBehavior(CameraPos, RockmanPos, SceneStage);
        }
    }
}

void EnemyManager::SetEnemies(std::vector<std::shared_ptr<Enemy>> enemy) {
    this->m_Enemies = enemy;
}
std::vector<std::shared_ptr<Enemy>> EnemyManager::GetEnemies() {
    return m_Enemies;
}
