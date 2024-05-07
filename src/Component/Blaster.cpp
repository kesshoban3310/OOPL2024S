//
// Created by User on 2024/4/26.
//
#include "Component/Blaster.hpp"
#include "Util/Time.hpp"

Blaster::Blaster(glm::vec2 pos, unsigned long animationinterval,
                 bool increase) {
    this->position = std::make_shared<glm::vec2>(pos);
    this->Collibox = std::make_shared<Collider>(
        this->position, glm::vec2{16 * 3, 16 * 3}, glm::vec2{0, 0});
    this->AnimationInterval = animationinterval;
    this->Open = increase;
    this->AmmoPath =
        RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/blaster/blaster5.png";
    Initialize();
}
void Blaster::Initialize() {
    for (int i = 1; i <= 4; i++) {
        std::string path = RESOURCE_DIR
                           "/Picture/Enemies/Bomb Man Stage/blaster/blaster" +
                           std::to_string(i) + ".png";
        ObjectPath.push_back(path);
    }
    Object = std::make_shared<ImageObject>(ObjectPath[0]);
    Object->SetScale({-3, 3});
    Object->SetPosition(*this->position);
    Object->SetZIndex(70);
    Object->SetVisible(true);
}
void Blaster::Behavior(glm::vec2 pos) {
    if (Open) {
        if (Util::Time::GetElapsedTimeMs() - AnimationTimer >
            AnimationInterval) {
            if (PathIndex < 3)
                PathIndex = PathIndex + 1;
            else {
                AnimationCount++;
                if (AnimationCount == 9) {
                    Shoot();
                }
                if (AnimationCount > 10) {
                    Open = 0;
                    AnimationCount = 0;
                }
            }
            Object->SetImage(ObjectPath[PathIndex]);
            AnimationTimer = Util::Time::GetElapsedTimeMs();
        }
    }
    else {
        if (Util::Time::GetElapsedTimeMs() - AnimationTimer >
            AnimationInterval) {
            if (PathIndex > 0)
                PathIndex = PathIndex - 1;
            else {
                AnimationCount++;
                if (AnimationCount > 10) {
                    Open = 1;
                    AnimationCount = 0;
                }
            }
            Object->SetImage(ObjectPath[PathIndex]);
            AnimationTimer = Util::Time::GetElapsedTimeMs();
        }
    }
}
void Blaster::Shoot() {
    glm::vec2 ammospeed = {360, 0};
    std::string path =
        RESOURCE_DIR "/Picture/Enemies/Bomb Man Stage/blaster/blaster5.png";
    glm::vec2 ammosize = {8 * 3, 8 * 3};
    std::shared_ptr<Ammo> ammo = std::make_shared<Ammo>(
        glm::vec2{position->x + 24, position->y}, ammospeed, path, ammosize);
    magazine.push_back(ammo);
}
