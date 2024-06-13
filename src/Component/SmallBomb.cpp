//
// Created by User on 2024/6/13.
//

#include "Component/SmallBomb.hpp"
#include "Util/Logger.hpp"

SmallBomb::SmallBomb(std::string imagePath, glm::vec2 startPosition, glm::vec2 expectedEndPosition, float expectedHeight,glm::vec2 storedPosition)
    : Enemy(StoredPosition,imagePath,1, false,glm::vec2 {24,24},Enemy::HurtState::COWARDLY){
    this->StartPosition = startPosition;
    this->EndPosition = expectedEndPosition;
    this->ExpectedHeight = expectedHeight;
    this->StoredPosition = storedPosition;
    this->ID = "Small Bomb";
}
void SmallBomb::DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage){
    float Dir = std::sqrt((RockmanPos.x-Position->x)*(RockmanPos.x-Position->x)+(RockmanPos.y-Position->y)*(RockmanPos.y-Position->y));
    if(Dir <= 80){
        BombombombCanMove = true;
        Reset();
    }
    if(Health < 0){
        BombombombCanMove = true;
        Reset();
    }
    else if(m_CanMove){
        BombombombCanMove = false;
        if(m_IsMoving){
            PhysicEngine();
        }
        else{
            SetVisable(true);
            TrajectCalculator();
            SetPosition(StartPosition);
        }
    }
    else{
        BombombombCanMove = true;
        Reset();
    }
}
void SmallBomb::PhysicEngine(){
    Position->x += m_XVelocity * Util::Time::GetDeltaTimeMs() * 0.5f;
    Position->y += m_YVelocity * Util::Time::GetDeltaTimeMs() * 0.5f;
    m_YVelocity -= Util::Time::GetDeltaTimeMs() * 0.5f / GRAVITY;
    SetPosition(*Position);
    float X = std::abs(Position->x - EndPosition.x);
    float Y = std::abs(Position->y - EndPosition.y);
    if(X <= 36 && Y <= 36){
        SetPosition(EndPosition);
        Reset();
    }
}
void SmallBomb::TrajectCalculator(){
    float JumpingTime = std::sqrt(2*std::abs(ExpectedHeight-StartPosition.y)*GRAVITY) + std::sqrt(2*std::abs(ExpectedHeight-EndPosition.y)*GRAVITY);
    m_XVelocity = (EndPosition.x - StartPosition.x) / JumpingTime;
    m_YVelocity = std::sqrt(2*std::abs(ExpectedHeight-StartPosition.y)*GRAVITY) / GRAVITY;
    m_IsMoving = true;
}
void SmallBomb::Reset(){
    SetPosition(StartPosition);
    SetHealth(1);
    SetLifeState(LifeState::LIFE);
    SetVisable(true);
    m_IsMoving = false;
    m_CanMove = false;
    m_XVelocity = 0.0;
    m_YVelocity = 0.0;
}
void SmallBomb::SetCanMove(bool canmove){
    m_CanMove = canmove;
}
bool SmallBomb::CanBombombombMove(){
    return BombombombCanMove;
}