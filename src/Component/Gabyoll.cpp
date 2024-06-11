//
// Created by User on 2024/5/13.
//
#include "Component/Gabyoll.hpp"
#include "Util/Logger.hpp"

#define PI 3.1415926535

Gabyoll::Gabyoll(glm::vec2 inipos, glm::vec2 finpos,glm::vec2 collidersize, std::vector<std::string> path, glm::vec2 speed, int health, bool visable, Enemy::HurtState hurtstate, Enemy::LifeState lifestate)
    : Enemy(inipos,path[0],health,visable,collidersize,hurtstate,lifestate){
    this->Path = path;
    this->Speed = speed;
    this->Inipos = inipos;
    this->length = glm::vec2 {finpos.x-inipos.x,finpos.y-inipos.y};
    this->Finpos = finpos;
};
void Gabyoll::DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) {
    float dirx = Position->x - CameraPos.x;
    if(Life == Enemy::LifeState::LIFE && (-384 <= dirx && dirx <= 384)){
        PhysicEngine();
    }
}
void Gabyoll::PhysicEngine() {
    if(Util::Time::GetElapsedTimeMs()-AnimationTimer>50) {
        AnimationTimer = Util::Time::GetElapsedTimeMs();
        switch (PathIdx) {
            case 0:
                PathIdx = 1;
                break;
            case 1:
                PathIdx = 0;
                break;
        }
        Object->SetImage(Path[PathIdx]);
        Position->x = Inipos.x + length.x * sin(Delta*PI/180.0f);
        Position->y = Inipos.y + length.y * sin(Delta*PI/180.0f);
        Object->SetPosition(*Position);
        Delta = (Delta+1) % 180;
    }
}
void Gabyoll::Reset() {
    *Position = InitialPos;
    Health = InitialHealth;
    Visable = InitialVisable;
    Life = InitialLife;
    Hurt = InitialHurt;
    PathIdx = 0;
    Delta = 0;
    Object->SetPosition(*Position);
    Object->SetVisible(Visable);
    Object->SetImage(Path[0]);
}