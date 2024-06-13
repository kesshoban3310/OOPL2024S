#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP

#include "Component/EnemyAttribute.hpp"
#include "pch.hpp"

class EnemyManager{
public:
    EnemyManager();
    void Update(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage);
    void Reset();
    void SetEnemies(std::vector<std::shared_ptr<Enemy>> enemy);
    void SetEnemyStage(std::unordered_map<std::string,std::vector<int> > enemystage);
    std::vector<std::shared_ptr<Enemy>> GetEnemies();
private:
    std::vector<std::shared_ptr<Enemy>> m_Enemies;
    std::unordered_map<std::string,std::vector<int> > m_EnemyStage;
};
#endif
