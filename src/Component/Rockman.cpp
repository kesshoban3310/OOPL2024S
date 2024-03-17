//
// Created by User on 2024/3/14.
//

#include "Component/Rockman.hpp"
#include "pch.hpp"
#include "Util/Time.hpp"
#include "Util/Keycode.hpp"
#include "Util/Input.hpp"

Rockman::Rockman() {

}

void Rockman::Initialize() {
    std::vector<std::string> Idlevec, Walkvec, Climbvec,Climbfinvec,Jumpvec;
    for (int i = 1; i <= 2; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Idle" +
                           std::to_string(i) + ".png";
        Idlevec.push_back(path);
    }
    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Walk" +
                           std::to_string(i) + ".png";
        Walkvec.push_back(path);
    }
    Walkvec.push_back(RESOURCE_DIR "/Picture/Character/Normal/Walk" +
                          std::to_string(2) + ".png");
    for (int i = 1; i <= 2; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Climb" +
                           std::to_string(i) + ".png";
        Climbvec.push_back(path);
    }
    Climbfinvec.push_back(RESOURCE_DIR "/Picture/Character/Normal/Climb" +
                          std::to_string(3) + ".png");
    Jumpvec.push_back(RESOURCE_DIR "/Picture/Character/Normal/Jump.png");
    std::shared_ptr<AnimatedObject> Idle =
        std::make_shared<AnimatedObject>(Idlevec, 1, 250);
    Idle->SetZIndex(3);
    Idle->SetScale({3,3});
    Idle->SetPosition(position);
    Idle->SetVisible(true);

    std::shared_ptr<AnimatedObject> Walk =
        std::make_shared<AnimatedObject>(Walkvec, 1, 160);
    Walk->SetZIndex(3);
    Walk->SetScale({3,3});
    Walk->SetPosition(position);
    Walk->SetVisible(false);

    std::shared_ptr<AnimatedObject> Climb =
        std::make_shared<AnimatedObject>(Climbvec, 1, 320);
    Climb->SetZIndex(3);
    Climb->SetScale({3,3});
    Climb->SetPosition(position);
    Climb->SetVisible(false);

    std::shared_ptr<AnimatedObject> Climbfin =
        std::make_shared<AnimatedObject>(Climbfinvec, 1, 120);
    Climbfin->SetZIndex(3);
    Climbfin->SetScale({3,3});
    Climbfin->SetPosition(position);
    Climbfin->SetVisible(false);

    std::shared_ptr<AnimatedObject> Jump =
        std::make_shared<AnimatedObject>(Jumpvec, 1, 120);
    Jump->SetZIndex(3);
    Jump->SetScale({3,3});
    Jump->SetPosition(position);
    Jump->SetVisible(false);
    character = {Idle,Walk,Climb,Climbfin,Jump};
}

void Rockman::Setposition(glm::vec2 position) {
    this->position = position;
    for(auto object:character)
        object->SetPosition(this->position);
}
void Rockman::Setvisable(const int &idx) {
    for(int i=0;i<character.size();i++){
        if(idx == i){
            character[i]->SetVisible(true);
        }
        else character[i]->SetVisible(false);
    }
}
glm::vec2 Rockman::Getposition() {
    return position;
}

void Rockman::move() {
    glm::vec2 pos = Getposition();
    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        pos.y = Util::Time::GetDeltaTime() * 800 + pos.y;
        Setvisable(4);
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        pos.y = Util::Time::GetDeltaTime() * (-160) + pos.y;
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        pos.x = Util::Time::GetDeltaTime() * (-160) + pos.x;
        Setvisable(1);
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        pos.x = Util::Time::GetDeltaTime() * 160 + pos.x;
    }
    Setposition(pos);
}