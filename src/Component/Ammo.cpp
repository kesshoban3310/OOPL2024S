//
// Created by User on 2024/3/22.
//
#include "Component/Ammo.hpp"
#include "Util/Keycode.hpp"
#include "Util/Time.hpp"

Ammo::Ammo(glm::vec2 position, glm::vec2 speed, std::string imagepath,
           glm::vec2 ammosize, AmmoType type) {
    this->path = imagepath;
    this->speed = speed;
    this->type = type;
    ammo = std::make_shared<ImageObject>(path);
    initial_position = std::make_shared<glm::vec2>(position);
    ammo->SetPosition(*initial_position);
    ammo->SetScale({3, 3});
    ammo->SetZIndex(70);
    ammo->SetVisible(true);

    final_position = position;
    if (speed.x != 0) {
        final_position.x += (speed.x / abs(speed.x)) * 768;
    }
    if (speed.y != 0) {
        final_position.y += (speed.y / abs(speed.y)) * 720;
    }
    colliderbox =
        std::make_shared<Collider>(initial_position, ammosize, glm::vec2{0, 0});
}
bool Ammo::Outofrange(glm::vec2 camerapos) { // need to add collision box;
    bool Xoverlap = false;
    bool Yoverlap = false;
    Xoverlap = camerapos.x - 384 >= initial_position->x ||
               camerapos.x + 384 <= initial_position->x;
    Yoverlap = camerapos.y - 360 >= initial_position->y ||
               camerapos.y + 360 <= initial_position->y;
    return Xoverlap || Yoverlap;
}
void Ammo::Behavior() {
    initial_position->x += (Util::Time::GetDeltaTimeMs() / 1000) * speed.x;
    initial_position->y += (Util::Time::GetDeltaTimeMs() / 1000) * speed.y;
    ammo->SetPosition(*initial_position);
}
