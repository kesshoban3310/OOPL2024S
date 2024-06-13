//
// Created by User on 2024/5/9.
//

// X: 6059
// X: 9169
// Y: -740
#include "Component/KillerBomb.hpp"
#include "Util/Logger.hpp"
#define PI 3.1415926535
KillerBomb::KillerBomb(glm::vec2 inipos, glm::vec2 speed, glm::vec2 scale,
                       std::string path, int health, bool visable)
    : Enemy(inipos, path, health, visable, {16 * 3, 16 * 3},
            Enemy::HurtState::COWARDLY) {
    this->Speed = speed;
    this->Scale = scale;
    this->Path = path;
    this->ID = "KillerBomb";
}

void KillerBomb::DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,int SceneStage) {
    bool CanMove = (CameraPos.x - 584 <= Position->x && Position->x <= CameraPos.x + 584) && (Health > 0);
    if (CanMove) {
        PhysicEngine();
    }
    else {
        if(Health<0){
            glm::vec2 NewPos = {-20000, -20000};
            SetPosition(NewPos);
        }
        if (CoolDownTimer == 0) {
            CoolDownTimer = Util::Time::GetElapsedTimeMs();
        }
        else if (Util::Time::GetElapsedTimeMs() - CoolDownTimer >
                 CoolDownTime) {
            glm::vec2 NewPos = {CameraPos.x + 500, RockmanPos.y};
            SetPosition(NewPos);
            Theta = 0;
            CoolDownTimer = 0;
            Health = 1;

        }
    }
}
void KillerBomb::PhysicEngine() {
    Position->x = Position->x + Speed.x * (Util::Time::GetDeltaTimeMs() / 1000);
    Position->y = Position->y + Speed.y * cos(Theta * PI / 180.0f) *
                                    (Util::Time::GetDeltaTimeMs() / 1000);
    Object->SetPosition(*Position);
    Theta = (Theta + 5) % 360;
}
void KillerBomb::Reset() {
    *Position = *Position + glm::vec2 {255,0};
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

void KillerBomb::SetHealth(int health) {
    Health = health;
}
int KillerBomb::GetHealth() {
    return Health;
}

void KillerBomb::SetVisable(bool visable) {
    Visable = visable;
    Object->SetVisible(Visable);
}
bool KillerBomb::GetVisable() {
    return Visable;
}
