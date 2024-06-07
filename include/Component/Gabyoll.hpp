#ifndef GABYOLL_HPP
#define GABYOLL_HPP

#include "Component/EnemyAttribute.hpp"
#include "Util/Time.hpp"
#include <cmath>
#include <pch.hpp>

// {8108,-1871},{8260,-1872}
// {8534,-1728},{8598,-1728}
// {8936,-2064},{7962,-2064}
class Gabyoll : public Enemy, Physic {
public:
    Gabyoll(glm::vec2 inipos, glm::vec2 finpos, glm::vec2 collidersize,
            std::vector<std::string> path, glm::vec2 speed, int health,
            bool visable, Enemy::HurtState hurtstate,
            Enemy::LifeState lifestate);
    void DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                    int SceneStage) override;
    void PhysicEngine() override;

private:
    std::vector<std::string> Path;
    glm::vec2 Speed;
    glm::vec2 Inipos, Finpos;
    glm::vec2 length;
    float AnimationTimer = 10;
    int PathIdx = 0;
    int delta = 0;
};

#endif
