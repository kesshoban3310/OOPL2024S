#ifndef KAMADOMA_HPP
#define KAMADOMA_HPP

#include "Component/EnemyAttribute.hpp"
#include "Component/ImageObject.hpp"
#include "Util/Time.hpp"
#include <algorithm>

/*
{glm::vec2 {72, -3600},
glm::vec2{312, -3600},
glm::vec2 {600, -3600},
glm::vec2 {835, -3493},
glm::vec2 {1031, -3396},
glm::vec2 {1226, -3301},
glm::vec2 {1356, -3397},
glm::vec2{1461, -3492},
glm::vec2{1607, -3600},
glm::vec2{1850, -3600},
glm::vec2{2132, -3600}}
 */
class Kamadoma : public Enemy, Physic {
public:
    Kamadoma(std::vector<std::string> path, std::vector<glm::vec2> points,
             glm::vec2 pos, int iniidx, glm::vec2 collidersize, int hp,
             bool visable, Enemy::HurtState hurtstate);
    void DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                    int SceneStage) override;
    void PhysicEngine() override;
    void TrajectoryCalculator(std::pair<glm::vec2, glm::vec2> point);
    bool Checker(glm::vec2 NowPos, glm::vec2 ExpectPos);

private:
    std::vector<std::string> Path;
    std::vector<glm::vec2> Points;
    int Idx;
    long long CoolDownTime = 500,
              CoolDownTimer = 0; // Free for next Jumping time.

    long long StartJumpingTime = 0, JumpingTimer = 0,
              JumpingTime = 3000; // Calculate Jumping Animation.

    glm::vec2 Speed;
    float JumpHigh = 122.5f;

    int SportTime = 0;
    int Theta = 0;
    glm::vec2 IniPos, FinPos;
    bool MoveLeft = true;
    bool IsJumping = false;
};
#endif
