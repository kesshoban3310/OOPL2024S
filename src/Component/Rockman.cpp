//
// Created by User on 2024/3/14.
//

#include "Component/Rockman.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Time.hpp"
#include "pch.hpp"

Rockman::Rockman(glm::vec2 pos, State Rockmanstate) {
    this->health = 28;
    this->Rockmanstate = Rockmanstate;
    this->position =
        std::make_shared<glm::vec2>(glm::vec2{pos.x - 36, pos.y - 133});
    healthbar = std::make_shared<Healthbar>(pos);
    collider.resize(2);
    collider[0] = std::make_shared<Collider>(
        position, glm::vec2{20 * 3, 12 * 3}, glm::vec2{0, 18});
    collider[1] = std::make_shared<Collider>(
        position, glm::vec2{20 * 3, 12 * 3}, glm::vec2{0, -18});
}

void Rockman::Initialize() {
    std::vector<std::string> Idlevec, Walkvec, Walkrightvec, Climbvec,
        Climbfinvec, Jumpvec, Deathvec;
    std::vector<std::string> Idleshootvec, Walkshootvec, Walkrightshootvec,
        Climbshootvec, Jumpshootvec;
    movetimer = -1;
    glm::vec2 pos = *position;
    /**
     * @brief Initialize normal.
     */
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
    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Walkright" +
                           std::to_string(i) + ".png";
        Walkrightvec.push_back(path);
    }
    Walkrightvec.push_back(RESOURCE_DIR "/Picture/Character/Normal/Walkright" +
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
    Idle->SetZIndex(ZIndex);
    Idle->SetScale(inversescale);
    Idle->SetPosition(pos);
    Idle->SetVisible(true);

    std::shared_ptr<AnimatedObject> Walk =
        std::make_shared<AnimatedObject>(Walkvec, 1, 160);
    Walk->SetZIndex(ZIndex);
    Walk->SetScale(scale);
    Walk->SetPosition(pos);
    Walk->SetVisible(false);

    std::shared_ptr<AnimatedObject> Walkright =
        std::make_shared<AnimatedObject>(Walkrightvec, 1, 160);
    Walkright->SetZIndex(ZIndex);
    Walkright->SetScale(scale);
    Walkright->SetPosition(pos);
    Walkright->SetVisible(false);

    std::shared_ptr<AnimatedObject> Climb =
        std::make_shared<AnimatedObject>(Climbvec, 1, 320);
    Climb->SetZIndex(ZIndex);
    Climb->SetScale(scale);
    Climb->SetPosition(pos);
    Climb->SetVisible(false);

    std::shared_ptr<AnimatedObject> Climbfin =
        std::make_shared<AnimatedObject>(Climbfinvec, 1, 120);
    Climbfin->SetZIndex(ZIndex);
    Climbfin->SetScale(scale);
    Climbfin->SetPosition(pos);
    Climbfin->SetVisible(false);

    std::shared_ptr<AnimatedObject> Jump =
        std::make_shared<AnimatedObject>(Jumpvec, 1, 120);
    Jump->SetZIndex(ZIndex);
    Jump->SetScale(scale);
    Jump->SetPosition(pos);
    Jump->SetVisible(false);

    std::shared_ptr<AnimatedObject> Jumpright =
        std::make_shared<AnimatedObject>(Jumpvec, 1, 120);
    Jumpright->SetZIndex(ZIndex);
    Jumpright->SetScale(inversescale);
    Jumpright->SetPosition(pos);
    Jumpright->SetVisible(false);

    /** @brief Initialize Death.
     */
    for (int i = 1; i <= 4; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Death" +
                           std::to_string(i) + ".png";
        Deathvec.push_back(path);
    }
    for (int i = 3; i >= 1; i--) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Death" +
                           std::to_string(i) + ".png";
        Deathvec.push_back(path);
    }

    for (int i = 0; i < 12; i++) {
        std::shared_ptr<AnimatedObject> Death =
            std::make_shared<AnimatedObject>(Deathvec, 1, 10);
        Death->SetZIndex(ZIndex);
        Death->SetScale(inversescale);
        Death->SetPosition(pos);
        Death->SetVisible(false);
        character_death.push_back(Death);
    }
    /** @brief Initialize Shoot.
     */
    Idleshootvec.push_back(RESOURCE_DIR "/Picture/Character/Shooting/Idle.png");

    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Shooting/Walk" +
                           std::to_string(i) + ".png";
        Walkshootvec.push_back(path);
    }
    Walkshootvec.push_back(RESOURCE_DIR
                           "/Picture/Character/Shooting/Walk2.png");

    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR
                           "/Picture/Character/Shooting/Walkright" +
                           std::to_string(i) + ".png";
        Walkrightshootvec.push_back(path);
    }
    Walkrightshootvec.push_back(RESOURCE_DIR
                                "/Picture/Character/Shooting/Walkright2.png");

    Climbshootvec.push_back(RESOURCE_DIR
                            "/Picture/Character/Shooting/Climb.png");

    Jumpshootvec.push_back(RESOURCE_DIR "/Picture/Character/Shooting/Jump.png");

    std::shared_ptr<AnimatedObject> Idleshoot =
        std::make_shared<AnimatedObject>(Idleshootvec, 1, 250);
    Idleshoot->SetZIndex(ZIndex);
    Idleshoot->SetScale(scale);
    Idleshoot->SetPosition(pos);
    Idleshoot->SetVisible(false);

    std::shared_ptr<AnimatedObject> Walkshoot =
        std::make_shared<AnimatedObject>(Walkshootvec, 1, 160);
    Walkshoot->SetZIndex(ZIndex);
    Walkshoot->SetScale(scale);
    Walkshoot->SetPosition(pos);
    Walkshoot->SetVisible(false);

    std::shared_ptr<AnimatedObject> Walkrightshoot =
        std::make_shared<AnimatedObject>(Walkrightshootvec, 1, 160);
    Walkrightshoot->SetZIndex(ZIndex);
    Walkrightshoot->SetScale(scale);
    Walkrightshoot->SetPosition(pos);
    Walkrightshoot->SetVisible(false);

    std::shared_ptr<AnimatedObject> Climbshoot =
        std::make_shared<AnimatedObject>(Climbshootvec, 1, 250);
    Climbshoot->SetZIndex(ZIndex);
    Climbshoot->SetScale(scale);
    Climbshoot->SetPosition(pos);
    Climbshoot->SetVisible(false);

    std::shared_ptr<AnimatedObject> Jumpshoot =
        std::make_shared<AnimatedObject>(Jumpshootvec, 1, 250);
    Jumpshoot->SetZIndex(ZIndex);
    Jumpshoot->SetScale(scale);
    Jumpshoot->SetPosition(pos);
    Jumpshoot->SetVisible(false);

    std::shared_ptr<AnimatedObject> Jumprightshoot =
        std::make_shared<AnimatedObject>(Jumpshootvec, 1, 250);
    Jumprightshoot->SetZIndex(ZIndex);
    Jumprightshoot->SetScale(inversescale);
    Jumprightshoot->SetPosition(pos);
    Jumprightshoot->SetVisible(false);

    if (!character_spawn.size()) {
        for (int i = 1; i <= 3; i++) {
            std::string path = RESOURCE_DIR "/Picture/Character/Spawn/Initial" +
                               std::to_string(i) + ".png";
            std::shared_ptr<ImageObject> Initial =
                std::make_shared<ImageObject>(path);
            Initial->SetPosition(pos);
            Initial->SetZIndex(ZIndex);
            Initial->SetScale(scale);
            Initial->SetVisible(false);
            character_spawn.push_back(Initial);
        }
        Sethealth(28);
    }
    character = {Idle, Walk, Walkright, Climb, Jump, Jumpright, Climbfin};
    character_shoot = {Idleshoot,  Walkshoot, Walkrightshoot,
                       Climbshoot, Jumpshoot, Jumprightshoot};
    Rockmanstate = State::Normal;
}

void Rockman::Spawn() {

    if (!character_spawn[0]->GetVisibility() && position->y == 430)
        character_spawn[0]->SetVisible(true);

    if (position->y > -145) {
        position->y += -25;
        character_spawn[0]->SetPosition(*position);
    }
    else {
        for (int i = 0; i <= 2; i++) {
            if (character_spawn[i]->GetVisibility()) {
                switch (i) {
                case 0:
                    character_spawn[1]->SetVisible(true);
                    character_spawn[1]->SetPosition(*position);
                    character_spawn[0]->SetVisible(false);
                    if (movetimer == -1)
                        movetimer = Util::Time::GetElapsedTimeMs();
                    break;
                case 1:
                    if (Util::Time::GetElapsedTimeMs() - movetimer < 15)
                        break;
                    position->y = -169;
                    character_spawn[2]->SetVisible(true);
                    character_spawn[2]->SetPosition(*position);
                    character_spawn[1]->SetVisible(false);
                    break;
                case 2:
                    if (Util::Time::GetElapsedTimeMs() - movetimer < 30)
                        break;
                    position->y = -145;
                    character_spawn[0]->SetVisible(true);
                    character_spawn[0]->SetPosition(*position);
                    character_spawn[2]->SetVisible(false);
                    Rockmanstate = State::Normal;
                    break;
                }
                break;
            }
        }
    }
}

void Rockman::behavior() {
    switch (Rockmanstate) {
    case State::Initial:
        Initialize();
        break;

    case State::Spawn:
        Spawn();
        break;

    case State::Normal:
        // if(character_spawn.size())
        //   character_spawn.clear();
        move();
        shoot();
        break;

    case State::Death:
        death();
        break;
    }
}

glm::vec2 Rockman::Getposition() {
    return *position;
}

void Rockman::Setposition(glm::vec2 pos) {
    *position = pos;
    for (auto object : character)
        object->SetPosition(pos);
}

void Rockman::Setvisable(const int &idx) {
    visable = idx;
    for (int i = 0; i < character.size(); i++) {
        if (idx == i) {
            character[i]->SetVisible(true);
        }
        else
            character[i]->SetVisible(false);
    }
}

void Rockman::move() { // Adjust Jump.
    Setvisable(0);
    glm::vec2 pos = Getposition();
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
        Setvisable(1);
        for (int i = 0; i < 10; i++) {
            pos.x = Util::Time::GetDeltaTime() * (-1.6) + pos.x;
            Setposition(pos);
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
        Setvisable(2);
        for (int i = 0; i < 10; i++) {
            pos.x = Util::Time::GetDeltaTime() * 1.6 + pos.x;
            Setposition(pos);
        }
    }

    if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
        // if no ledder is collision,then use this
        pos.y = Util::Time::GetDeltaTime() * (160) + pos.y;
        is_jumping = 1; // jumping 138 pixel.
    }
    /*
    if(is_jumping && Util::Input::IsKeyPressed(Util::Keycode::UP) &&
    pos.y<=initial_pos.y+140){ if (visable == 1) { Setvisable(4);
        }
        else if(visable == 2 || visable == 0) {
            Setvisable(5);
        }
        if(initial_pos.x == -1 && initial_pos.y == -1){
            initial_pos = pos;
        }
        if(Jump_bar == -1){
            Jump_bar = 1.0/Util::Time::GetDeltaTime()*0.6;
        }
        pos.y += Jump_bar;
    }
     */
    if (Util::Input::IsKeyPressed(Util::Keycode::DOWN)) {
        pos.y = Util::Time::GetDeltaTime() * (-160) + pos.y;
    }
    /*
    if(is_jumping && pos.y-140>=initial_pos.y) {
       is_jumping = 0;
       is_falling = 1;
    }
    if(is_falling){
       if(pos.y>=initial_pos.y)
            pos.y-=Jump_bar;
    }
     */
    Setposition(pos);
}

void Rockman::death() {
    if (visable != -1)
        Setvisable(-1);
    if (!character_death[0]->GetVisibility()) {
        for (int i = 0; i < 12; i++) {
            character_death[i]->SetPosition(*position);
            character_death[i]->SetVisible(true);
        }
    }
    if (character_death[0]->GetPosition().x > position->x + 150)
        return;

    int negative = 1;
    for (int i = 0; i < 4; i++) {
        auto delta = Util::Time::GetDeltaTime();
        auto position = character_death[i]->GetPosition();
        if (!(i & 1)) {
            character_death[i]->SetPosition(
                {position.x + 60 * delta * negative, position.y});
        }
        else {
            character_death[i]->SetPosition(
                {position.x, position.y + 60 * delta * negative});
            negative *= -1;
        }
    }
    negative = 1;
    for (int i = 4; i < 8; i++) {
        auto delta = Util::Time::GetDeltaTime();
        auto position = character_death[i]->GetPosition();
        if (!(i & 1)) {
            character_death[i]->SetPosition(
                {position.x + 120 * delta * negative, position.y});
        }
        else {
            character_death[i]->SetPosition(
                {position.x, position.y + 120 * delta * negative});
            negative *= -1;
        }
    }
    int negative_x = 1, negative_y = 1;
    for (int i = 8; i < 12; i++) {
        auto delta = Util::Time::GetDeltaTime();
        auto position = character_death[i]->GetPosition();
        if (!(i & 1)) {
            character_death[i]->SetPosition(
                {position.x + 86.6 * delta * negative_x,
                 position.y + 86.6 * delta * negative_y});
            negative_x *= -1;
        }
        else {
            character_death[i]->SetPosition(
                {position.x + 86.6 * delta * negative_x,
                 position.y + 86.6 * delta * negative_y});
            negative_y *= -1;
        }
    }
}

int Rockman::Gethealth() {
    return health;
}
void Rockman::Sethealth(int hp) {
    if (hp < 0 || hp > 28)
        return;
    health = hp;
    healthbar->SetVisable(health);
    if (!health) {
        Rockmanstate = State::Death;
    }
}

void Rockman::shoot() {
    if (Util::Input::IsKeyDown(Util::Keycode::X)) {
        Setshootvisable(visable, true);
        int direction = 0;
        if (visable == 2 || visable == 5)
            direction = 1;
        std::shared_ptr<Ammo> ammo =
            std::make_shared<Ammo>(*position, direction);
        magazine.push_back(ammo);
        shoottimer = Util::Time::GetElapsedTimeMs();
        return;
    }
    if (Util::Time::GetElapsedTimeMs() - shoottimer > 35) {
        Setshootvisable(visable, false);
        shoottimer = -1;
    }
}
void Rockman::Setshootvisable(const int &idx, bool visable) {
    character[idx]->SetVisible(!visable);
    character_shoot[idx]->SetVisible(visable);
    character_shoot[idx]->SetPosition(*position);
}

Rockman::State Rockman::Getcurrentstate() {
    return Rockmanstate;
}

std::vector<std::shared_ptr<Util::GameObject>> Rockman::GetAllchildren() {
    std::vector<std::shared_ptr<Util::GameObject>> Object,
        Barobject = healthbar->GetChildren();
    for (auto i : character_spawn)
        Object.push_back(i);
    for (auto i : character)
        Object.push_back(i);
    for (auto i : character_death)
        Object.push_back(i);
    for (auto i : character_shoot)
        Object.push_back(i);
    for (auto i : Barobject)
        Object.push_back(i);
    return Object;
}
[[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>>
Rockman::Getchildren(Rockman::State state) {
    std::vector<std::shared_ptr<Util::GameObject>> Object;
    switch (state) {
    case State::Spawn:
        for (auto i : character_spawn)
            Object.push_back(i);
        break;

    case State::Normal:
        for (auto i : character)
            Object.push_back(i);
        for (auto i : character_shoot)
            Object.push_back(i);
        break;

    case State::Death:
        for (auto i : character_death)
            Object.push_back(i);
        break;
    }
    return Object;
}
