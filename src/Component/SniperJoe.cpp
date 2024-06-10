//
// Created by User on 2024/5/14.
//

#include "Component/SniperJoe.hpp"
#include "Util/Logger.hpp"
#define PI 3.1415926535

SniperJoe::SniperJoe(glm::vec2 inipos, glm::vec2 finpos, glm::vec2 collidersize,
                     glm::vec2 speed, glm::vec2 ammospeed,
                     std::vector<std::string> path, std::string ammopath,
                     int health, bool visable, Enemy::HurtState hurtstate,
                     Enemy::LifeState lifestate)
    : Enemy(inipos, path[1], health, visable, collidersize, hurtstate,
            lifestate) {
    this->Path = path;
    this->IniPos = inipos;
    this->FinPos = finpos;
    this->AmmoPath = ammopath;
    this->Speed = speed;
    this->AmmoSpeed = ammospeed;
}
void SniperJoe::DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                           int SceneStage) {
    float dir_x = Position->x - RockmanPos.x;
    if (dir_x >= 0) {
        if (MoveState == PhysicState::BYCHOICE) {
            MoveState = PhysicState::STAND;
            StandTimer = Util::Time::GetElapsedTimeMs();
        }
        else {
            auto NowTime = Util::Time::GetElapsedTimeMs();
            switch (MoveState) {
            case PhysicState::SHOOT:
                Object->SetImage(Path[2]);
                if (ShootCounter == ShootCount) {
                    MoveState = PhysicState::INVINCIBLE;
                    Object->SetImage(Path[1]);
                    ShootCounter = 0;
                    ShootTimer = 0;
                    InvincibleTimer = NowTime;
                }
                if ((NowTime - ShootTimer) > 800) {
                    Shoot();
                    ShootTimer = Util::Time::GetElapsedTimeMs();
                    ShootCounter++;
                }
                break;
            case PhysicState::JUMP:
                PhysicEngine();
                Object->SetImage(Path[3]);
                if (JumpCounter == JumpCount) {
                    MoveState = PhysicState::STAND;
                    JumpCounter = 0;
                    StandTimer = NowTime;
                }
                break;
            case PhysicState::STAND:
                Object->SetImage(Path[1]);
                Object->SetScale({3, 3});
                if (NowTime - StandTimer > StandTime) {
                    MoveState = PhysicState::SHOOT;
                    StandTimer = 0;
                    ShootTimer = NowTime;
                    ShootCounter = 0;
                }
                break;
            case PhysicState::INVINCIBLE:
                Object->SetImage(Path[0]);
                if (NowTime - InvincibleTimer > InvincibleTime) {
                    MoveState = PhysicState::JUMP;
                    Object->SetImage(Path[1]);
                    InvincibleTimer = 0;
                }
                break;
            case PhysicState::MOVE:
                if (JumpTheta != 0) {
                    MoveState = PhysicState::JUMP;
                }
                else
                    MoveState = PhysicState::BYCHOICE;
                break;
            }
        }
    }
    else {
        MoveState = PhysicState::MOVE;
        Object->SetImage(Path[3]);
        PhysicEngine();
    }
}
void SniperJoe::PhysicEngine() {
    JumpTheta = (JumpTheta + 5) % 180;
    if (MoveState == PhysicState::MOVE) {
        Object->SetScale({-3, 3});
        if (Position->x < FinPos.x) {
            Position->x =
                Position->x + Util::Time::GetDeltaTimeMs() / 1000 * 160;
        }
        Position->y = IniPos.y + JumpHigh.y * sin(JumpTheta * PI / 180.0f);
        Object->SetPosition(*Position);
    }
    else {
        Position->y = IniPos.y + JumpHigh.y * sin(JumpTheta * PI / 180.0f);
        Object->SetPosition(*Position);
        if (JumpTheta == 0) {
            JumpCounter++;
        }
    }
}
void SniperJoe::Shoot() {
    std::shared_ptr<Ammo> ammo =
        std::make_shared<Ammo>(*Position, AmmoSpeed, AmmoPath,
                               glm::vec2{8 * 3, 8 * 3}, AmmoType::ENEMY);
    Magazine.push_back(ammo);
}
void SniperJoe::Reset() {
    *Position = InitialPos;
    Health = InitialHealth;
    Visable = InitialVisable;
    Life = InitialLife;
    Hurt = InitialHurt;
    MoveState = PhysicState::BYCHOICE;
    StandTimer = 0;
    ShootCounter = 0;
    JumpCounter = 0;
    InvincibleTimer = 0;
    ShootTimer = 0;
    Object->SetPosition(*Position);
    Object->SetImage(Path[1]);
    Object->SetVisible(Visable);
    Magazine.clear();
}
/*
void SniperJoe::DeBugMessage() {
    LOG_INFO("SniperJoe");
    switch (MoveState) {
    case PhysicState::SHOOT:
        LOG_INFO("SHOOT");
        break;
    case PhysicState::JUMP:
        LOG_INFO("JUMP");
        break;
    case PhysicState::STAND:
        LOG_INFO("STAND");
        break;
    case PhysicState::INVINCIBLE:
        LOG_INFO("INVINCIBLE");
        break;
    case PhysicState::MOVE:
        LOG_INFO("MOVE");
        break;
    case PhysicState::BYCHOICE:
        LOG_INFO("BYCHOICE");
        break;
    }
}
*/