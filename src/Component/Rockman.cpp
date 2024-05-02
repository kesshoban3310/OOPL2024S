//
// Created by User on 2024/3/14.
//

#include "Component/Rockman.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Time.hpp"
#include "pch.hpp"

/* TODO: Modify Shooting System.
 * TODO: Adding Hurt System.
 * TODO: Modify Switching Image System.
 */

Rockman::Rockman(glm::vec2 pos, LiveState Rockmanstate) {
    this->health = 28;
    this->RockmanState = Rockmanstate;
    this->position = std::make_shared<glm::vec2>(glm::vec2{pos.x, pos.y});
    healthbar = std::make_shared<Healthbar>(pos);
    MoveState = PhysicState::MOVE;
    collider.resize(2);
    collider[0] = std::make_shared<Collider>(
        position, glm::vec2{20 * 3, 12 * 3}, glm::vec2{0, 24});
    collider[1] = std::make_shared<Collider>(
        position, glm::vec2{20 * 3, 12 * 3}, glm::vec2{0, -24});
}

void Rockman::Initialize() {
    std::vector<std::string> Idlevec, Walkvec, Walkrightvec, Climbvec,
        Climbfinvec, Jumpvec, Deathvec;
    std::vector<std::string> Idleshootvec, Walkshootvec, Walkrightshootvec,
        Climbshootvec, Jumpshootvec;
    movetimer = 0;
    glm::vec2 pos = *position;
    /**
     * @brief Initialize normal.
     */
    for (int i = 1; i <= 2; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Idle" +
                           std::to_string(i) + ".png";
        Idlevec.emplace_back(path);
    }
    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Walk" +
                           std::to_string(i) + ".png";
        Walkvec.emplace_back(path);
    }
    Walkvec.push_back(RESOURCE_DIR "/Picture/Character/Normal/Walk" +
                      std::to_string(2) + ".png");
    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Walkright" +
                           std::to_string(i) + ".png";
        Walkrightvec.emplace_back(path);
    }
    Walkrightvec.push_back(RESOURCE_DIR "/Picture/Character/Normal/Walkright" +
                           std::to_string(2) + ".png");
    for (int i = 1; i <= 2; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Climb" +
                           std::to_string(i) + ".png";
        Climbvec.emplace_back(path);
    }
    Climbfinvec.push_back(RESOURCE_DIR "/Picture/Character/Normal/Climb" +
                          std::to_string(3) + ".png");
    Jumpvec.emplace_back(RESOURCE_DIR "/Picture/Character/Normal/Jump.png");

    std::shared_ptr<AnimatedObject> Idle =
        std::make_shared<AnimatedObject>(Idlevec, 1, 250);
    Idle->SetZIndex(ZIndex);
    Idle->SetScale(inversescale);
    Idle->SetPosition(pos);
    Idle->SetVisible(false);

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
        Deathvec.emplace_back(path);
    }
    for (int i = 3; i >= 1; i--) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Death" +
                           std::to_string(i) + ".png";
        Deathvec.emplace_back(path);
    }

    for (int i = 0; i < 12; i++) {
        std::shared_ptr<AnimatedObject> Death =
            std::make_shared<AnimatedObject>(Deathvec, 1, 10);
        Death->SetZIndex(ZIndex);
        Death->SetScale(inversescale);
        Death->SetPosition(pos);
        Death->SetVisible(false);
        character_death.emplace_back(Death);
    }
    /** @brief Initialize Shoot.
     */
    Idleshootvec.emplace_back(RESOURCE_DIR
                              "/Picture/Character/Shooting/Idle.png");

    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Shooting/Walk" +
                           std::to_string(i) + ".png";
        Walkshootvec.emplace_back(path);
    }
    Walkshootvec.emplace_back(RESOURCE_DIR
                              "/Picture/Character/Shooting/Walk2.png");

    for (int i = 1; i <= 3; i++) {
        std::string path = RESOURCE_DIR
                           "/Picture/Character/Shooting/Walkright" +
                           std::to_string(i) + ".png";
        Walkrightshootvec.emplace_back(path);
    }
    Walkrightshootvec.emplace_back(
        RESOURCE_DIR "/Picture/Character/Shooting/Walkright2.png");

    Climbshootvec.emplace_back(RESOURCE_DIR
                               "/Picture/Character/Shooting/Climb.png");

    Jumpshootvec.emplace_back(RESOURCE_DIR
                              "/Picture/Character/Shooting/Jump.png");

    std::shared_ptr<AnimatedObject> Idleshoot =
        std::make_shared<AnimatedObject>(Idleshootvec, 1, 250);
    Idleshoot->SetZIndex(ZIndex);
    Idleshoot->SetScale(inversescale);
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

    if (character_spawn.empty()) {
        for (int i = 1; i <= 3; i++) {
            std::string path = RESOURCE_DIR "/Picture/Character/Spawn/Initial" +
                               std::to_string(i) + ".png";
            std::shared_ptr<ImageObject> Initial =
                std::make_shared<ImageObject>(path);
            Initial->SetPosition(pos);
            Initial->SetZIndex(ZIndex);
            Initial->SetScale(scale);
            Initial->SetVisible(false);
            character_spawn.emplace_back(Initial);
        }
        Sethealth(28);
    }
    character = {Idle, Walk, Walkright, Climb, Jump, Jumpright, Climbfin};
    character_shoot = {Idleshoot,  Walkshoot, Walkrightshoot,
                       Climbshoot, Jumpshoot, Jumprightshoot};
    RockmanState = LiveState::Spawn;
}

void Rockman::Spawn(std::vector<std::shared_ptr<TileBox>> collison) {
    if (!character_spawn[0]->GetVisibility() && movetimer == 0)
        character_spawn[0]->SetVisible(true);
    std::set<RockmanCollison> RockmanCollisonState = GetCollison(collison);
    if (!RockmanCollisonState.count(RockmanCollison::BOTTOM)) {
        for (int i = 0; i < 5; i++) {
            std::set<RockmanCollison> RockmanCollisonState =
                GetCollison(collison);
            if (!RockmanCollisonState.count(RockmanCollison::BOTTOM)) {
                position->y -= 16;
                Setposition(*position);
                character_spawn[0]->SetPosition(*position);
            }
            else
                break;
        }
    }
    else {
        for (int i = 0; i <= 2; i++) {
            if (character_spawn[i]->GetVisibility()) {
                switch (i) {
                case 0:
                    character_spawn[1]->SetVisible(true);
                    character_spawn[1]->SetPosition(*position);
                    character_spawn[0]->SetVisible(false);
                    if (movetimer == 0)
                        movetimer = Util::Time::GetElapsedTimeMs();
                    break;
                case 1:
                    if (Util::Time::GetElapsedTimeMs() - movetimer < 33)
                        break;
                    character_spawn[2]->SetVisible(true);
                    character_spawn[2]->SetPosition(*position);
                    character_spawn[1]->SetVisible(false);
                    break;
                case 2:
                    if (Util::Time::GetElapsedTimeMs() - movetimer < 50)
                        break;
                    position->y -= 6;
                    character[0]->SetVisible(true);
                    character[0]->SetPosition(*position);
                    character_spawn[2]->SetVisible(false);
                    collider.clear();
                    collider[0] = std::make_shared<Collider>(
                        position, glm::vec2{20 * 3, 12 * 3}, glm::vec2{0, 18});
                    collider[1] = std::make_shared<Collider>(
                        position, glm::vec2{20 * 3, 12 * 3}, glm::vec2{0, -18});
                    RockmanState = LiveState::Normal;
                    break;
                }
                break;
            }
        }
    }
}

void Rockman::Behavior(std::vector<std::shared_ptr<TileBox>> collison) {
    std::set<RockmanCollison> collisonstate = GetCollison(collison);

    switch (RockmanState) {
    case LiveState::Initial:
        Initialize();
        break;

    case LiveState::Spawn:
        Spawn(collison);
        break;

    case LiveState::Normal:
        PhysicEngine(collisonstate, collison);
        Shoot();
        break;

    case LiveState::Death:
        Death();
        break;
    }
}

glm::vec2 Rockman::Getposition() {
    return *position;
}

void Rockman::Setposition(glm::vec2 pos) {
    for (auto object : character)
        object->SetPosition({pos.x, pos.y});
    *position = pos;
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

void Rockman::PhysicEngine(std::set<RockmanCollison> collison,
                           std::vector<std::shared_ptr<TileBox>> collisonbox) {
    // TODO: Modify Climb System, Import Shoot.
    Ladder_Pos = {-2000,-2000};
    if (MoveState == PhysicState::MOVE)
        Setvisable(0);
    if (MoveState == PhysicState::JUMP) {
        Jump(collisonbox);
    }
    // DebugMessageCollidor(collison, "PhysicEngine");
    if (MoveState == PhysicState::CLIMB) { // Climb if state is climb.
        Climb(collisonbox);
        return;
    }
    DebugMessagePhysic(MoveState);
    glm::vec2 pos = Getposition();
    if (Util::Input::IsKeyPressed(Util::Keycode::UP) &&
        collison.count(
            RockmanCollison::ROCKMANINLADDER)) // If State isn't Climb and can
                                               // Climb,then climb.
        Climb(collisonbox);
    if (MoveState == Rockman::PhysicState::MOVE) { // Move Left or Right
        if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
            Setvisable(1);
            for (int i = 0; i < 10; i++) {
                if (collison.count(RockmanCollison::UPLEFT) &&
                    collison.count(RockmanCollison::DOWNLEFT))
                    break;
                pos.x = Util::Time::GetDeltaTime() * (-16) + pos.x;
                Setposition(pos);
            }
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
            Setvisable(2);
            for (int i = 0; i < 10; i++) {
                if (collison.count(RockmanCollison::UPRIGHT) &&
                    collison.count(RockmanCollison::DOWNRIGHT))
                    break;
                pos.x = Util::Time::GetDeltaTime() * 16 + pos.x;
                Setposition(pos);
            }
        }
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::X) && // Jumping
        (MoveState != PhysicState::FALL ||
         MoveState != PhysicState::JUMPBEFOREFALL)) {
        if (MoveState != PhysicState::JUMPBEFOREMOVE)
            Jump(collisonbox);
    }
    if (!Util::Input::IsKeyPressed(Util::Keycode::X) && // De-jumping
        MoveState  == PhysicState::JUMPBEFOREMOVE) {
        MoveState = PhysicState::MOVE;
    }
    collison = GetCollison(collisonbox);
    if (MoveState != PhysicState::CLIMB) { // Falling Detect.
        if (MoveState == PhysicState::JUMPBEFOREFALL) {
            MoveState = PhysicState::FALL;
        }
        if (MoveState == PhysicState::MOVE) {
            if(collison.count(RockmanCollison::BOTTEMINLADDER)) {
                if(collison.count(RockmanCollison::ROCKMANINLADDER))
                    MoveState = PhysicState::FALL;
            }
            else if(!collison.count(RockmanCollison::BOTTOM))
                MoveState = PhysicState::FALL;
        }
        if (MoveState == PhysicState::FALL) {
            Fall(collisonbox);
        }
    }
    if(MoveState == PhysicState::CLIMBFIN){ //De-Climbing
        Setposition({position->x,position->y-48});
        MoveState = PhysicState::MOVE;
    }
    if ((collison.count(RockmanCollison::BOTTOM) &&
         MoveState == PhysicState::JUMPBEFOREFALL)) { // De-Jumping
        if (character[4]->GetVisibility() || character[5]->GetVisibility()) {
            if (Util::Input::IsKeyPressed(Util::Keycode::X))
                MoveState = PhysicState::JUMPBEFOREMOVE;
            if (!Util::Input::IsKeyPressed(Util::Keycode::X))
                MoveState = PhysicState::MOVE;
            Setvisable(0);
        }
    }
    if (Util::Input::IsKeyPressed(
            Util::Keycode::DOWN)) { // Test, it can't not use when Release.
        if (collison.count(RockmanCollison::BOTTEMINLADDER)) {
            Setposition({position->x, position->y - 16 * 3});
            Climb(collisonbox);
        }
        else {
            //pos.y = Util::Time::GetDeltaTime() * (-160) + pos.y;
            //Setposition(pos);
        }
    }
}

void Rockman::Climb(std::vector<std::shared_ptr<TileBox>> collison) {
    auto CollisonResult = GetCollison(collison);
    if (MoveState != PhysicState::CLIMB) {
        MoveState = PhysicState::CLIMB;
        Setposition({Ladder_Pos.x,position->y});
        Ladder_Pos = {-2000,-2000};
    }
    glm::vec2 pos = Getposition();
    for (int i = 0; i < 10; i++) {
        CollisonResult = GetCollison(collison);
        if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
            pos.y += 32 * Util::Time::GetDeltaTime();
        }

        if (Util::Input::IsKeyPressed(Util::Keycode::DOWN) && !CollisonResult.count(RockmanCollison::BOTTOM) ) {
            pos.y -= 32 * Util::Time::GetDeltaTime();
        }
        else if(Util::Input::IsKeyPressed(Util::Keycode::DOWN) && CollisonResult.count(RockmanCollison::BOTTOM) ){
            Setvisable(0);
            Setposition({pos.x,pos.y+72});
            MoveState = PhysicState::CLIMBFIN;
            return;
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::X)) {
            Setvisable(5);
            MoveState = PhysicState::FALL;
            return;
        }
        if (!CollisonResult.count(RockmanCollison::ROCKMANINLADDER)) {
            Setvisable(6);
        }
        else {
            Setvisable(3);
        }
        if (!CollisonResult.count(RockmanCollison::ROCKMANINLADDER)) {
            Setvisable(0);
            Setposition({pos.x, pos.y+48});
            MoveState = PhysicState::CLIMBFIN;
            return;
        }
    }
    CollisonResult = GetCollison(collison);
    DebugMessageCollidor(CollisonResult, "Climb");
    Setposition(pos);
}

void Rockman::Death() {
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
        RockmanState = LiveState::Death;
    }
}

void Rockman::Shoot() {
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        Setshootvisable(visable, true);
        if (MoveState == PhysicState::MOVE)
            MoveState = PhysicState::SHOOT;
        glm::vec2 ammo_position = {position->x + 35, position->y + 5};
        glm::vec2 direction = {-20, 0};
        if (visable == 2 || visable == 5 || visable == 0) {
            direction = {20, 0};
            ammo_position = {ammo_position.x - 41, ammo_position.y + 4};
        }
        if (visable == 5)
            ammo_position = {ammo_position.x + 36, ammo_position.y + 14};
        if (visable == 4)
            ammo_position = {ammo_position.x - 36, ammo_position.y + 14};
        std::shared_ptr<Ammo> ammo = std::make_shared<Ammo>(
            ammo_position, direction,
            RESOURCE_DIR "/Picture/Character/Shooting/Ammo.png",
            glm::vec2{8 * 3, 8 * 3});
        magazine.push_back(ammo);
        shoottimer = Util::Time::GetElapsedTimeMs();
        return;
    }
    if (Util::Time::GetElapsedTimeMs() - shoottimer > 100 && shoottimer != 0) {
        Setshootvisable(visable, false);
        if (MoveState == PhysicState::SHOOT)
            MoveState = PhysicState::MOVE;
        shoottimer = 0;
    }
}
void Rockman::Setshootvisable(const int &idx, bool visable) {
    character[idx]->SetVisible(!visable);
    character_shoot[idx]->SetPosition(*position);
    character_shoot[idx]->SetVisible(visable);
}
std::set<Rockman::RockmanCollison>
Rockman::GetCollison(std::vector<std::shared_ptr<TileBox>> collison) {
    std::set<RockmanCollison> box;
    for (int i = 0; i < collison.size(); i++) {
        Collider rockmanup = *collider[0], rockmandown = *collider[1];
        if (collison[i]->GetObjectType() == TileBox::ObjectType::CLIMB) {

            if(IsColliding(rockmandown, *(collison[i]->Getcollisonbox()))){
                bool OverLap = IfColliginIsInside(
                    rockmandown, *(collison[i]->Getcollisonbox()));
                auto CollisonResult = WhereIsColliding(rockmandown, *(collison[i]->Getcollisonbox()));
                if (OverLap) {
                    if(glm::vec2 {-2000,-2000} == Ladder_Pos){
                        Ladder_Pos = collison[i]->GetPosition();
                    }
                    box.insert(RockmanCollison::ROCKMANINLADDER);
                }
                if(CollisonResult.count(Collider::Bound::BOTTOM)){
                    box.insert(RockmanCollison::BOTTEMINLADDER);
                }
            }
            continue;
        }
        if (IsColliding(rockmanup, *(collison[i]->Getcollisonbox()))) {
            auto collisonresult =
                WhereIsColliding(rockmanup, *(collison[i]->Getcollisonbox()));
            if (collisonresult.count(Collider::Bound::TOP))
                box.insert(RockmanCollison::TOP);
            if (collisonresult.count(Collider::Bound::LEFT))
                box.insert(RockmanCollison::UPLEFT);
            if (collisonresult.count(Collider::Bound::RIGHT))
                box.insert(RockmanCollison::UPRIGHT);
        }
        if (IsColliding(rockmandown, *(collison[i]->Getcollisonbox()))) {
            auto collisonresult =
                WhereIsColliding(rockmandown, *(collison[i]->Getcollisonbox()));
            if (collisonresult.count(Collider::Bound::LEFT))
                box.insert(RockmanCollison::DOWNLEFT);
            if (collisonresult.count(Collider::Bound::RIGHT))
                box.insert(RockmanCollison::DOWNRIGHT);
            if (collisonresult.count(Collider::Bound::BOTTOM))
                box.insert(RockmanCollison::BOTTOM);
        }
    }
    return box;
}

Rockman::LiveState Rockman::Getcurrentstate() {
    return RockmanState;
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
std::vector<std::shared_ptr<Util::GameObject>>
Rockman::Getchildren(LiveState state) {
    std::vector<std::shared_ptr<Util::GameObject>> Object;
    switch (state) {
    case LiveState::Spawn:
        for (auto i : character_spawn)
            Object.push_back(i);
        break;

    case LiveState::Normal:
        for (auto i : character)
            Object.push_back(i);
        for (auto i : character_shoot)
            Object.push_back(i);
        break;

    case LiveState::Death:
        for (auto i : character_death)
            Object.push_back(i);
        break;
    }
    return Object;
}
void Rockman::Jump(std::vector<std::shared_ptr<TileBox>> collison) {
    glm::vec2 pos = *position;
    auto result = GetCollison(collison);
    if (MoveState == PhysicState::FALL ||
        MoveState == PhysicState::JUMPBEFOREFALL)
        return;
    if (MoveState != PhysicState::JUMP) {
        if (result.count(RockmanCollison::TOP))
            return;
        MoveState = PhysicState::JUMP;
        Initial_Pos = pos;
        if (visable == 0 || visable == 2)
            Setvisable(5);
        if (visable == 1)
            Setvisable(4);
        Setposition(pos);
        jumptimer = Util::Time::GetElapsedTimeMs();
        return;
    }
    if (MoveState == PhysicState::JUMP &&
        Util::Time::GetElapsedTimeMs() - jumptimer > (18)) {
        jumptimer = Util::Time::GetElapsedTimeMs();
        for (int i = 0; i < 6; i++) {
            if (pos.y <= Initial_Pos.y + 162 &&
                Util::Input::IsKeyPressed(Util::Keycode::X)) {
                result = GetCollison(collison);
                if (result.count(RockmanCollison::TOP)) {
                    MoveState = PhysicState::JUMPBEFOREFALL;
                    jumptimer = 0;
                    return;
                }
                if (!result.count(RockmanCollison::DOWNRIGHT) &&
                    !result.count(RockmanCollison::UPRIGHT) &&
                    Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
                    pos.x += 64 * Util::Time::GetDeltaTime();
                }
                if (!result.count(RockmanCollison::DOWNLEFT) &&
                    !result.count(RockmanCollison::UPLEFT) &&
                    Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
                    pos.x -= 64 * Util::Time::GetDeltaTime();
                }
                pos.y += 120 * Util::Time::GetDeltaTime();
                Setposition(pos);
            }
            else {
                MoveState = PhysicState::JUMPBEFOREFALL;
                jumptimer = 0;
                return;
            }
        }
    }
}
void Rockman::Fall(std::vector<std::shared_ptr<TileBox>> collison) {
    if (falltimer == 0)
        falltimer = Util::Time::GetElapsedTimeMs();
    if (MoveState == PhysicState::FALL &&
        Util::Time::GetElapsedTimeMs() - falltimer > (18)) {
        glm::vec2 pos = *position;
        falltimer = Util::Time::GetElapsedTimeMs();
        for (int i = 0; i < 6; i++) {
            auto result = GetCollison(collison);
            DebugMessageCollidor(result,"Fall");
            bool CanFall = (!result.count(RockmanCollison::BOTTOM) && !result.count(RockmanCollison::BOTTEMINLADDER)) || (result.count(RockmanCollison::BOTTEMINLADDER) && result.count(RockmanCollison::ROCKMANINLADDER));
            if (CanFall) {
                pos.y -= 60 * Util::Time::GetDeltaTime();
                if (!result.count(RockmanCollison::DOWNRIGHT) && !result.count(RockmanCollison::UPRIGHT) && Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
                    pos.x += 64 * Util::Time::GetDeltaTime();
                }
                if (!result.count(RockmanCollison::DOWNLEFT) && !result.count(RockmanCollison::UPLEFT) && Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
                    pos.x -= 64 * Util::Time::GetDeltaTime();
                }
                Setposition(pos);
            }
            else {
                if (MoveState == PhysicState::FALL)
                    MoveState = PhysicState::MOVE;
                else
                    MoveState = PhysicState::JUMPBEFOREMOVE;
                Setvisable(0);
                falltimer = 0;
            }
        }
    }
}
void Rockman::DebugMessageCollidor(std::set<RockmanCollison> collidorstate,std::string locate) {
    LOG_DEBUG("=========" + locate + "============");
    for (auto test : collidorstate) {
        switch (test) {
        case RockmanCollison::UPRIGHT:
            LOG_DEBUG("UPRIGHT");
            break;
        case RockmanCollison::UPLEFT:
            LOG_DEBUG("UPLEFT");
            break;
        case RockmanCollison::TOP:
            LOG_DEBUG("TOP");
            break;
        case RockmanCollison::BOTTOM:
            LOG_DEBUG("BOTTOM");
            break;
        case RockmanCollison::DOWNRIGHT:
            LOG_DEBUG("DOWNRIGHT");
            break;
        case RockmanCollison::DOWNLEFT:
            LOG_DEBUG("DOWNLEFT");
            break;
        case RockmanCollison::BOTTEMINLADDER:
            LOG_DEBUG("BOTTEMINLADDER");
            break;
        case RockmanCollison::ROCKMANINLADDER:
            LOG_DEBUG("ROCKMANINLADDER");
            break;
        }
    }
    LOG_DEBUG("=====================");
}
void Rockman::DebugMessagePhysic(PhysicState physicState) {
    switch (physicState) {
    case PhysicState::JUMP:
        LOG_DEBUG("JUMP");
        break;
    case PhysicState::MOVE:
        LOG_DEBUG("MOVE");
        break;
    case PhysicState::CLIMB:
        LOG_DEBUG("CLIMB");
        break;
    case PhysicState::FALL:
        LOG_DEBUG("FALL");
        break;
    case PhysicState::SHOOT:
        LOG_DEBUG("SHOOT");
        break;
    case PhysicState::JUMPBEFOREFALL:
        LOG_DEBUG("JUMPBEFOREFALL");
        break;
    case PhysicState::JUMPBEFOREMOVE:
        LOG_DEBUG("JUMPBEFOREMOVE");
        break;
    }
}
