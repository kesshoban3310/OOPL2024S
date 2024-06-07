//
// Created by User on 2024/5/10.
//

#include "Component/Mambu.hpp"
#define PI 3.1415926535

Mambu::Mambu(glm::vec2 pos,std::vector<std::string> path,glm::vec2 speed,glm::vec2 ammospeed,std::string ammopath,glm::vec2 collidersize,int health,bool visable)
: Enemy(pos,path[0],health,visable,collidersize, Enemy::HurtState::INVINCIBLE){
    this->Path = path;
    this->Speed = speed;
    this->AmmoSpeed = ammospeed;
    this->AmmoPath = ammopath;
}
void Mambu::DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) {
    DiffWithCamX = Position->x - CameraPos.x;
    if(-484 <= DiffWithCamX && DiffWithCamX <= 584)
        PhysicEngine();
    else if(-584 <= DiffWithCamX && DiffWithCamX <= -384){
        Object->SetImage(Path[0]);
        if(!Magazine.empty())
            Magazine.clear();
        Position->x = CameraPos.x + 684;
        Object->SetPosition(*Position);
    }
}
void Mambu::PhysicEngine() {
    if(Object->GetImagePath() == Path[0]) {
        Position->x =
            Position->x + Speed.x * (Util::Time::GetDeltaTimeMs() / 1000);
        Position->y =
            Position->y + Speed.y * (Util::Time::GetDeltaTimeMs() / 1000);
        Object->SetPosition(*Position);
        CircumlateX += std::abs(Speed.x * (Util::Time::GetDeltaTimeMs() / 1000));
    }
    else{
        if(Util::Time::GetElapsedTimeMs()-AnimationTimer>=200){
            Object->SetImage(Path[0]);
            AnimationTimer = 0;
        }
    }
    if(CircumlateX >= 250){
        Object->SetImage(Path[1]);
        if(-384 <= DiffWithCamX && DiffWithCamX <= 384)
            Shoot();
        AnimationTimer = Util::Time::GetElapsedTimeMs();
        CircumlateX = 0;
    }
}
void Mambu::Shoot() {
    float Theta = 0;
    for(int i=0;i<8;i++){
        float ammospeed_x = AmmoSpeed.x * cos(Theta * PI / 180.0f);
        float ammospeed_y = AmmoSpeed.y * sin(Theta * PI / 180.0f);
        std::shared_ptr<Ammo> ammo = std::make_shared<Ammo>(*Position,
                                                            glm::vec2 {ammospeed_x,ammospeed_y},
                                                            AmmoPath,
                                                            glm::vec2 {8*3,8*3},
                                                            AmmoType::ENEMY);
        Theta += 45;
        Magazine.push_back(ammo);
    }
}