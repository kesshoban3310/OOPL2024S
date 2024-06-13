//
// Created by User on 2024/5/3.
//

#include "Component/Bombombomb.hpp"

// Enemy Position
// 2515 -3950
// 2900 -3950
// 3285 -3950
// 3670 -3950

//Bomb Position
// 2278 -3526 {-238,-286}
// 2394 -3426 {-121,-186}
// 2697 -3526 {182,-286}
// 2789 -3426 {274,-186}




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
            Split();
    }
    else{ //Set to Initial.
        Object->SetPosition(InitialPosition);
        *Position = InitialPosition;
        WaitingCounter = 0;
        BeSmallBomb = 0;
    }
}
void Bombombomb::PhysicEngine() {
    if (Util::Time::GetElapsedTimeMs() - WaitingCounter <= 3000) {
        return;
    }
    if (FinalPosition.y >= Position->y) {
        Position->y += Speed.y;
        Object->SetPosition(*Position);
    }
    else {
        BeSmallBomb = 1;
        Position->y = InitialPosition.y;
        Object->SetPosition(*Position);
        Object->SetVisible(true);
    }
}
void Bombombomb::Split() {
    std::vector<glm::vec2> PositionOffset = {{-238,-286},
                                              {-121,-186},
                                              {182,-286},
                                              {274,-186}};
    for(int i=0;i<4;i++){
        float High = -3420 + 16;
        glm::vec2 StartPosition = FinalPosition;
        glm::vec2 EndPosition = {InitialPosition.x+PositionOffset[i].x,InitialPosition.y+PositionOffset[i].y};
        std::shared_ptr<Bomb> bomb = std::make_shared<Bomb>(AmmoPath,StartPosition,EndPosition,High);
        SmallBomb.push_back(bomb);
    }
    BeSmallBomb = 0;
}
void Bombombomb::Reset() {
    *Position = InitialPos;
    Health = InitialHealth;
    Visable = InitialVisable;
    Life = InitialLife;
    Hurt = InitialHurt;
    Object->SetPosition(*Position);
    Object->SetVisible(Visable);
    Object->SetImage(Path);
    WaitingCounter = 0;
    BeSmallBomb = 0;
}