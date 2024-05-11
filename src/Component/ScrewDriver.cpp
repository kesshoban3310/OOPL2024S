//
// Created by User on 2024/4/26.
//
#include "Component/ScrewDriver.hpp"
#include "Util/Time.hpp"
#include <cmath>

#define PI 3.1415926535

Screwdriver::Screwdriver(glm::vec2 pos) {
    this->position = std::make_shared<glm::vec2>(pos);
    this->Collibox = std::make_shared<Collider>(
        this->position, glm::vec2{16 * 3, 16 * 3}, glm::vec2{0, 0});
    Initialize();
}
void Screwdriver::Initialize() {
    for (int i = 1; i <= 5; i++) {
        std::string path =
            RESOURCE_DIR
            "/Picture/Enemies/Bomb Man Stage/ScrewDriver/ScrewDriver" +
            std::to_string(i) + ".png";
        ObjectPath.push_back(path);
    }
    Object = std::make_shared<ImageObject>(ObjectPath[0]);
    Object->SetScale({3, 3});
    Object->SetPosition(*this->position);
    Object->SetZIndex(70);
    Object->SetVisible(true);
}
void Screwdriver::Behavior(glm::vec2 pos) {
    double Distance = sqrt(((pos.x - position->x) * (pos.x - position->x)) +
                           ((pos.y - position->y) * (pos.y - position->y)));
    if (Distance <= 250)
        StartUp = 1;
    if (StartUp) {
        if (Open) {
            if (Util::Time::GetElapsedTimeMs() - AnimationTimer >
                AnimationInterval) {
                PathIndex = PathIndex + 1;
                if (PathIndex >= 5)
                    PathIndex = 2;
                AnimationCount++;
                if (AnimationCount == 7 || AnimationCount == 13) {
                    Shoot();
                }
                if (AnimationCount > 15) {
                    Open = 0;
                    AnimationCount = 0;
                }
                Object->SetImage(ObjectPath[PathIndex]);
                AnimationTimer = Util::Time::GetElapsedTimeMs();
            }
        }
        else if (!Open) {
            if (Util::Time::GetElapsedTimeMs() - AnimationTimer >
                AnimationInterval) {
                if (PathIndex > 0)
                    PathIndex = PathIndex - 1;
                else {
                    AnimationCount++;
                    if (AnimationCount > 10) {
                        Open = 1;
                        AnimationCount = 0;
                        StartUp = 0;
                    }
                }
                Object->SetImage(ObjectPath[PathIndex]);
                AnimationTimer = Util::Time::GetElapsedTimeMs();
            }
        }
    }
}
void Screwdriver::Shoot() {
    glm::vec2 ammospeed;
    std::string path = RESOURCE_DIR
        "/Picture/Enemies/Bomb Man Stage/ScrewDriver/ScrewDriver6.png";
    glm::vec2 ammosize = {8 * 3, 8 * 3};
    float theta = 0;
    for (int i = 0; i < 5; i++) {
        ammospeed = {320 * cos(theta * PI / 180.0f),
                     320 * sin(theta * PI / 180.0f)};
        std::shared_ptr<Ammo> ammo = std::make_shared<Ammo>(
            glm::vec2{position->x, position->y}, ammospeed, path, ammosize, AmmoType::ENEMY);
        if (i > 0 && i < 3)
            theta += 30;
        else
            theta += 60;
        magazine.push_back(ammo);
    }
}
