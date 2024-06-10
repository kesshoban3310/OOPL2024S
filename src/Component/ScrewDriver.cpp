//
// Created by User on 2024/4/26.
//
#include "Component/ScrewDriver.hpp"
#include "Util/Time.hpp"
#include <cmath>

#define PI 3.1415926535

Screwdriver::Screwdriver(glm::vec2 pos,glm::vec2 scale,glm::vec2 collidersize,std::vector<std::string> path,std::string ammopath,Enemy::LifeState lifestate,Enemy::HurtState hurtstate,int health,bool visable)
    : Enemy(pos,path[0],health,visable,collidersize,hurtstate,lifestate,scale){
    this->ObjectPath = path;
    this->AmmoPath = ammopath;
}
void Screwdriver::DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                             int SceneStage) {
    double Distance =
        sqrt(((RockmanPos.x - Position->x) * (RockmanPos.x - Position->x)) +
             ((RockmanPos.y - Position->y) * (RockmanPos.y - Position->y)));
    if (Distance <= 250)
        StartUp = true;
    if (StartUp) {
        if (Open) {
            if (Util::Time::GetElapsedTimeMs() - AnimationTimer >
                AnimationInterval) {
                PathIndex = PathIndex + 1;
                if (PathIndex >= 5)
                    PathIndex = 2;
                AnimationCount++;
                if (AnimationCount == 7 || AnimationCount == 13) {
                    Shoot();
                }
                if (AnimationCount > 15) {
                    Open = false;
                    AnimationCount = 0;
                }
                Object->SetImage(ObjectPath[PathIndex]);
                AnimationTimer = Util::Time::GetElapsedTimeMs();
            }
        }
        else if (!Open) {
            if (Util::Time::GetElapsedTimeMs() - AnimationTimer >
                AnimationInterval) {
                if (PathIndex > 0)
                    PathIndex = PathIndex - 1;
                else {
                    AnimationCount++;
                    if (AnimationCount > 10) {
                        Open = true;
                        AnimationCount = 0;
                        StartUp = false;
                    }
                }
                Object->SetImage(ObjectPath[PathIndex]);
                AnimationTimer = Util::Time::GetElapsedTimeMs();
            }
        }
    }
}
void Screwdriver::Shoot() {
    glm::vec2 ammospeed;
    glm::vec2 ammosize = {8 * 3, 8 * 3};
    float theta = 0;
    for (int i = 0; i < 5; i++) {
        ammospeed = {320 * cos(theta * PI / 180.0f),
                     320 * sin(theta * PI / 180.0f)};
        std::shared_ptr<Ammo> ammo = std::make_shared<Ammo>(
            glm::vec2{Position->x, Position->y}, ammospeed, AmmoPath, ammosize,AmmoType::ENEMY);
        if (i > 0 && i < 3)
            theta += 30;
        else
            theta += 60;
        Magazine.push_back(ammo);
    }
}
void Screwdriver::Reset() {
    *Position = InitialPos;
    Health = InitialHealth;
    Visable = InitialVisable;
    Life = InitialLife;
    Hurt = InitialHurt;
    AnimationTimer = 0;
    AnimationInterval = 60;
    AnimationCount = 0;
    Open = 0;
    StartUp = 0;
    PathIndex = 0;
    Object->SetPosition(*Position);
    Object->SetVisible(Visable);
    Object->SetImage(ObjectPath[0]);
}

