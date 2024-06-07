#ifndef SNIPER_JOE_HPP
#define SNIPER_JOE_HPP

#include "Component/Ammo.hpp"
#include "Component/EnemyAttribute.hpp"
#include "Util/Time.hpp"
#include <cstdlib>
#include <time.h>

class SniperJoe : public Enemy, Physic, Shootable {
public:
    enum class PhysicState {
        SHOOT,
        JUMP,
        MOVE,
        STAND,
        BYCHOICE,
        INVINCIBLE,
    };
    SniperJoe(glm::vec2 inipos, glm::vec2 finpos, glm::vec2 collidersize,
              glm::vec2 speed, glm::vec2 ammospeed,
              std::vector<std::string> path, std::string ammopath, int health,
              bool visable, Enemy::HurtState hurtstate,
              Enemy::LifeState lifestate);
    void DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                    int SceneStage) override;
    void PhysicEngine() override;
    void Shoot() override;
    [[nodiscard]] std::vector<std::shared_ptr<Ammo>> GetAmmo() {
        std::vector<std::shared_ptr<Ammo>> magazine = Magazine;
        Magazine.clear();
        return magazine;
    }

private:
    std::vector<std::string> Path;
    std::string AmmoPath;
    glm::vec2 LeftScale = {3, 3};
    glm::vec2 Speed;
    glm::vec2 AmmoSpeed;
    glm::vec2 JumpHigh = {0, 160};
    glm::vec2 IniPos, FinPos;
    std::vector<std::shared_ptr<Ammo>> Magazine;
    int JumpTheta = 0;
    PhysicState MoveState = PhysicState::BYCHOICE;
    float InvincibleTime = 2000, InvincibleTimer = 0;
    float ShootTimer = 0;
    float StandTime = 2500, StandTimer = 0;
    int ShootCount = 3, ShootCounter = 0;
    int JumpCount = 1, JumpCounter = 0;

    void DeBugMessage();
};
#endif
