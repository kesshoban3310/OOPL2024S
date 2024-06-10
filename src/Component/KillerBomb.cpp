//
// Created by User on 2024/5/9.
//


//X: 6059
//X: 9169
//Y: -740
#include "Component/KillerBomb.hpp"
#define PI 3.1415926535
KillerBomb::KillerBomb(glm::vec2 inipos,glm::vec2 speed,glm::vec2 scale,std::string path,int health,bool visable)
    : Enemy(inipos,path,health,visable,{16*3,16*3},Enemy::HurtState::COWARDLY){
    this->Speed = speed;
    this->Scale = scale;
    this->Path = path;
}

void KillerBomb::DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) {
    bool Exist = (6059 <= RockmanPos.x && RockmanPos.x <= 9169) && RockmanPos.y <= -740;
    bool CanMove = CameraPos.x - 584 <= Position->x && Position->x <= CameraPos.x + 584;
    if(Exist) {
        if(CanMove) {
            PhysicEngine();
        }
        else {
            if(CoolDownTimer == 0){
                CoolDownTimer = Util::Time::GetElapsedTimeMs();
            }
            else if(Util::Time::GetElapsedTimeMs()-CoolDownTimer>CoolDownTime){
                glm::vec2 NewPos = {CameraPos.x + 500, CameraPos.y};
                SetPosition(NewPos);
                Theta = 0;
                CoolDownTimer = 0;
            }
        }
    }
    else{
        SetPosition(glm::vec2 {-20000,-20000});
    }
}
void KillerBomb::PhysicEngine() {
    Position->x = Position->x + Speed.x * (Util::Time::GetDeltaTimeMs()/1000);
    Position->y = Position->y + Speed.y * cos(Theta * PI / 180.0f) * (Util::Time::GetDeltaTimeMs()/1000);
    Object->SetPosition(*Position);
    Theta = (Theta+5) % 360;
}
void KillerBomb::Reset() {
    *Position = InitialPos;
    Health = InitialHealth;
    Visable = InitialVisable;
    Life = InitialLife;
    Hurt = InitialHurt;
    CoolDownTimer = 0;
    Theta = 0;
    Object->SetPosition(*Position);
    Object->SetVisible(Visable);
    Object->SetImage(Path);
}



void KillerBomb::SetHealth(int health){
    Health = health;
}
int KillerBomb::GetHealth(){
    return Health;
}

void KillerBomb::SetVisable(bool visable){
    Visable = visable;
    Object->SetVisible(Visable);
}
bool KillerBomb::GetVisable(){
    return Visable;
}