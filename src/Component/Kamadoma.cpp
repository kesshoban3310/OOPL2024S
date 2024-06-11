//
// Created by User on 2024/5/25.
//

#include "Component/Kamadoma.hpp"
#include "Util/Logger.hpp"

#define Gravity 200.0f

Kamadoma::Kamadoma(std::vector<std::string> path, std::vector<glm::vec2> points,
                   glm::vec2 pos, int iniidx, glm::vec2 collidersize, int hp,
                   bool visable, Enemy::HurtState hurtstate)
    : Enemy(pos, path[0], hp, visable, collidersize, hurtstate) {
    this->Path = path;
    this->Points = points;
    this->Idx = iniidx;
}
void Kamadoma::DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                          int SceneStage) {
    float RockmanPosX = Position->x - RockmanPos.x;
    if (RockmanPosX >= 1500)
        return;
    PhysicEngine();
}
void Kamadoma::PhysicEngine() {
    glm::vec2 StartPoint = Points[Idx];
    if (IsJumping) {
        if (Checker(*Position, FinPos)) {
            *Position = FinPos;
            Object->SetImage(Path[2]);
            CoolDownTimer = Util::Time::GetElapsedTimeMs();
            Object->SetPosition(*Position);
            IsJumping = false;
            return;
        }
        float scaledTime = Util::Time::GetDeltaTimeMs() * 0.5f;
        float NewX = Position->x + Speed.x * scaledTime;
        float NewY = Position->y + Speed.y * scaledTime;
        Speed.y -= scaledTime / Gravity;
        *Position = glm::vec2{NewX, NewY};
        Object->SetPosition(*Position);
        JumpingTimer = Util::Time::GetElapsedTimeMs();
    }
    else {
        if (Util::Time::GetElapsedTimeMs() - CoolDownTimer < CoolDownTime) {
            return;
        }
        Object->SetImage(Path[1]);
        glm::vec2 EndPoint;
        if (MoveLeft) {
            if (Idx == 0) {
                EndPoint = Points[2];
                Idx = 2;
                MoveLeft = false;
            }
            else {
                Idx--;
                EndPoint = Points[Idx];
            }
        }
        else {
            if (Idx == Points.size() - 1) {
                EndPoint = Points[Points.size() - 3];
                Idx = Points.size() - 3;
                MoveLeft = true;
            }
            else {
                Idx++;
                EndPoint = Points[Idx];
            }
        }
        IniPos = StartPoint, FinPos = EndPoint;
        TrajectoryCalculator({StartPoint, EndPoint});
        IsJumping = true;
        JumpingTimer = Util::Time::GetElapsedTimeMs();
        StartJumpingTime = Util::Time::GetElapsedTimeMs();
    }
}
void Kamadoma::TrajectoryCalculator(std::pair<glm::vec2, glm::vec2> point) {
    float RealHigh = std::max(point.first.y, point.second.y) + JumpHigh;
    JumpingTime = std::sqrt(2 * std::abs(RealHigh - point.first.y) * Gravity) +
                  std::sqrt(2 * std::abs(RealHigh - point.second.y) * Gravity);
    Speed.x = (point.second.x - point.first.x) / JumpingTime;
    Speed.y =
        std::sqrt(2 * std::abs(RealHigh - point.first.y) * Gravity) / Gravity;
}

bool Kamadoma::Checker(glm::vec2 NowPos, glm::vec2 ExpectPos) {
    float X = std::abs(NowPos.x - ExpectPos.x);
    float Y = std::abs(NowPos.y - ExpectPos.y);
    return X <= 36 && Y <= 36;
}
