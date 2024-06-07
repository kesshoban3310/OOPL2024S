#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP

#include "Component/EnemyAttribute.hpp"

class EnemyManager {
public:
    EnemyManager();
    void Update(glm::vec2 CameraPos, glm::vec2 RockmanPos, int SceneStage);
    void SetEnemies(std::vector<std::shared_ptr<Enemy>> enemy);
    std::vector<std::shared_ptr<Enemy>> GetEnemies();

private:
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
};
#endif
