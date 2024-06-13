//
// Created by User on 2024/5/13.
//
#include "Component/Gabyoll.hpp"
#include "Util/Logger.hpp"
#include "algorithm"
#define PI 3.1415926535

Gabyoll::Gabyoll(glm::vec2 inipos, glm::vec2 finpos,glm::vec2 collidersize, std::vector<std::string> path, glm::vec2 speed, int health, bool visable, Enemy::HurtState hurtstate, Enemy::LifeState lifestate)
    : Enemy(inipos,path[0],health,visable,collidersize,hurtstate,lifestate){
    this->Path = path;
    this->Inipos = inipos;
    this->Finpos = finpos;
    this->Speed = speed;
    if(Finpos.x -Inipos.x < 0) Speed.x*=(-1);
    if(Finpos.y -Inipos.y  < 0) Speed.y*=(-1);
    this->ID = "Gabyoll";
};
void Gabyoll::DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) {
    if(Life == Enemy::LifeState::LIFE){
        PhysicEngine();
    }
}
void Gabyoll::PhysicEngine() {
    switch (PathIdx) {
        case 0:
            PathIdx = 1;
            break;
        case 1:
            PathIdx = 0;
            break;
    }
    Object->SetImage(Path[PathIdx]);
    Position->x = Position->x + Speed.x * (Util::Time::GetDeltaTimeMs() / 1000.0);
    Position->y = Position->y + Speed.y * (Util::Time::GetDeltaTimeMs() / 1000.0);
    float Dir = std::sqrt((Position->x-Finpos.x)*(Position->x-Finpos.x)+(Position->y-Finpos.y)*(Position->y-Finpos.y));
    if(Dir <= 4.0){
        *Position = Finpos;
        std::swap(Inipos,Finpos);
        Speed *= glm::vec2 {-1,-1};
    }
    Object->SetPosition(*Position);
}
void Gabyoll::Reset() {
    *Position = InitialPos;
    Health = InitialHealth;
    Visable = InitialVisable;
    Life = InitialLife;
    Hurt = InitialHurt;
    PathIdx = 0;
    Object->SetPosition(*Position);
    Object->SetVisible(Visable);
    Object->SetImage(Path[0]);
}