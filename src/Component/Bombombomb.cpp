//
// Created by User on 2024/5/3.
//

#include "Component/Bombombomb.hpp"

// Enemy Position
// 2515 -3950
// 2900 -3950
// 3285 -3950
// 3670 -3950

// Y axis From -3950 to -3240
Bombombomb::Bombombomb(glm::vec2 pos, glm::vec2 speed, glm::vec2 ammospeed,
                       glm::vec2 scale, glm::vec2 colldiersize,std::string path,
                       std::string ammopath,int health,bool visable,Enemy::HurtState hurtState)
: Enemy(pos,path,health,visable,colldiersize,hurtState){
    this->Path = path;
    this->AmmoPath =  ammopath;
    this->InitialPosition = pos;
    this->FinalPosition = glm::vec2{pos.x, -3240};
    this->Speed = speed;
    this->Scale = scale;
    this->AmmoSpeed = ammospeed;
}

void Bombombomb::DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) {
    float direction = sqrt((CameraPos.x-Position->x)*(CameraPos.x-Position->x) + (CameraPos.y-Position->y)*(CameraPos.y-Position->y));
    if(direction <= 630) {
        if(!BeSmallBomb)
            PhysicEngine();
        else
            SmallBombMove();
    }
    else{ //Set to Initial.
        Object->SetPosition(InitialPosition);
        *Position = InitialPosition;
        WaitingCounter = 0;
        BeSmallBomb = 0;
    }
}
void Bombombomb::PhysicEngine() {
    if (Util::Time::GetElapsedTimeMs() - WaitingCounter <= 1500) {
        return;
    }
    if (FinalPosition.y >= Position->y) {
        Position->y += Speed.y;
        Object->SetPosition(*Position);
    }
    else {
        Split();
        BeSmallBomb = 1;
        Position->y = InitialPosition.y;
        Object->SetPosition(*Position);
        Object->SetVisible(true);
    }
}
void Bombombomb::Split() {
    for(int i=0;i<4;i++){

    }
}
void Bombombomb::SmallBombMove() {

}
