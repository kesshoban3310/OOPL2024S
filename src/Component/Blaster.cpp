//
// Created by User on 2024/4/26.
//
#include "Component/Blaster.hpp"
#include "Util/Time.hpp"

Blaster::Blaster(glm::vec2 pos, glm::vec2 collidersize, glm::vec2 scale,
                 unsigned long animationinterval, bool increase,
                 std::vector<std::string> path, std::string ammopath,
                 int health, bool visable, Enemy::HurtState hurtstate,
                 Enemy::LifeState lifestate)
    : Enemy(pos, path[0], health, visable, collidersize, hurtstate, lifestate,
            scale) {
    this->AnimationInterval = animationinterval;
    this->Open = increase;
    this->AmmoPath = ammopath;
    this->Path = path;
    this->ID = "Blaster";
}

void Blaster::DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) {
    if (Open) {
        Hurt = Enemy::HurtState::COWARDLY;
        if (Util::Time::GetElapsedTimeMs() - AnimationTimer >
            AnimationInterval) {
            if (PathIndex < 3)
                PathIndex = PathIndex + 1;
            else {
                AnimationCount++;
                if (AnimationCount == 9) {
                    Shoot();
                }
                if (AnimationCount > 10) {
                    Open = 0;
                    AnimationCount = 0;
                }
            }
            Object->SetImage(Path[PathIndex]);
            AnimationTimer = Util::Time::GetElapsedTimeMs();
        }
    }
    else {
        Hurt = Enemy::HurtState::INVINCIBLE;
        if (Util::Time::GetElapsedTimeMs() - AnimationTimer >
            AnimationInterval) {
            if (PathIndex > 0)
                PathIndex = PathIndex - 1;
            else {
                AnimationCount++;
                if (AnimationCount > 10) {
                    Open = 1;
                    AnimationCount = 0;
                }
            }
            Object->SetImage(Path[PathIndex]);
            AnimationTimer = Util::Time::GetElapsedTimeMs();
        }
    }
}
void Blaster::Shoot() {
    glm::vec2 ammospeed = {360, 0};
    glm::vec2 ammosize = {8 * 3, 8 * 3};
    std::shared_ptr<Ammo> ammo = std::make_shared<Ammo>(
        glm::vec2{Position->x + 24, Position->y}, ammospeed, AmmoPath, ammosize,
        AmmoType::ENEMY);
    Magazine.push_back(ammo);
}
void Blaster::Reset() {
    *Position = InitialPos;
    Health = InitialHealth;
    Visable = InitialVisable;
    Life = InitialLife;
    Hurt = InitialHurt;
    AnimationTimer = 0;
    AnimationCount = 0;
    PathIndex = 0;
    Open = 1;
    Object->SetPosition(*Position);
    Object->SetVisible(Visable);
    Object->SetImage(Path[0]);
    Magazine.clear();
}