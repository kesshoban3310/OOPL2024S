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
                       glm::vec2 scale, std::string path,
                       std::string ammopath) {
    this->Path = RESOURCE_DIR + path;
    this->AmmoPath = RESOURCE_DIR + ammopath;
    this->InitialPosition = pos;
    this->FinalPosition = glm::vec2{pos.x, -3240};
    this->Position = std::make_shared<glm::vec2>(pos);
    this->Speed = speed;
    this->Scale = scale;
    this->AmmoSpeed = ammospeed;
    this->Collisonbox = std::make_shared<Collider>(
        Position, glm::vec2{16 * scale.x, 16 * scale.y}, glm::vec2{0, 0});
    Initialize();
}
void Bombombomb::Initialize() {
    Object = std::make_shared<ImageObject>(Path);
    Object->SetPosition(*Position);
    Object->SetScale(Scale);
    Object->SetVisible(true);
    Object->SetZIndex(70);
}
void Bombombomb::Behavior(glm::vec2 position) {
    float direction = sqrt((position.x-Position->x)*(position.x-Position->x) + (position.y-Position->y)*(position.y-Position->y));
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
