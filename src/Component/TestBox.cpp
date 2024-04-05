//
// Created by User on 2024/4/5.
//

#include "Component/TestBox.hpp"
#include "Util/Keycode.hpp"
#include "Util/Input.hpp"
#include "Util/Time.hpp"

TestBox::TestBox(glm::vec2 pos,glm::vec2 sca) {
    this->position = std::make_shared<glm::vec2>(pos);
    this->scale = sca;
    std::string path = RESOURCE_DIR "/Picture/Tiles/Bomb Man Stage/Object/6.png";
    Object = std::make_shared<ImageObject>(path);
    Object->SetPosition(pos);
    Object->SetScale(scale);
    Object->SetZIndex(70);
    Object->SetVisible(true);

    collisonbox = std::make_shared<Collider>(this->position,glm::vec2 {16*scale.x,16*scale.y},glm::vec2 {0,0});
}
void TestBox::Move() {
    glm::vec2 pos = *position;
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        for (int i = 0; i < 10; i++) {
            pos.x = Util::Time::GetDeltaTime() * (-16) + pos.x;
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        for (int i = 0; i < 10; i++) {
            pos.x = Util::Time::GetDeltaTime() * 16 + pos.x;
        }
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::UP) ) {
        pos.y = Util::Time::GetDeltaTime() * (160) + pos.y;
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        pos.y = Util::Time::GetDeltaTime() * (-160) + pos.y;
    }
    *position = pos;
    Object->SetPosition(*position);
}