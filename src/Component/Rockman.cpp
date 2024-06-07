//
// Created by User on 2024/3/14.
//

#include "Component/Rockman.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Time.hpp"
#include "pch.hpp"

/*
 * TODO: Adding Hurt System.
 */

Rockman::Rockman(glm::vec2 pos, LiveState Rockmanstate) {
    this->Health = 28;
    this->RockmanState = Rockmanstate;
    this->Position = std::make_shared<glm::vec2>(glm::vec2{pos.x, pos.y});
    MoveState = PhysicState::MOVE;
    Initialize();
    ColliderBox.resize(2);
    ColliderBox[0] = std::make_shared<Collider>(
        Position, glm::vec2{20 * 3, 12 * 3}, glm::vec2{0, 24});
    ColliderBox[1] = std::make_shared<Collider>(
        Position, glm::vec2{20 * 3, 12 * 3}, glm::vec2{0, -24});
}

void Rockman::Initialize() {
    std::vector<std::string> Idlevec, Walkvec, Climbvec, Jumpvec, Deathvec;
    std::string Idleshootvec, Walkshootvec, Climbshootvec, Jumpshootvec;
    MoveTimer = 0;

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

    Jumpvec.emplace_back(RESOURCE_DIR "/Picture/Character/Normal/Jump.png");

    CharacterAnimatePath = {Idlevec, Walkvec, Jumpvec};

    for (int i = 1; i <= 2; i++) {
        std::string path = RESOURCE_DIR "/Picture/Character/Normal/Climb" +
                           std::to_string(i) + ".png";
        CharacterImagePath.emplace_back(path);
    }

    /** @brief Get Shoot Image Path.
     */
    Idleshootvec = RESOURCE_DIR "/Picture/Character/Shooting/Idle.png";

    Walkshootvec = RESOURCE_DIR "/Picture/Character/Shooting/Walk1.png";

    Jumpshootvec = RESOURCE_DIR "/Picture/Character/Shooting/Jump.png";

    Climbshootvec = RESOURCE_DIR "/Picture/Character/Shooting/Climb.png";

    CharacterShootPath = {Idleshootvec, Walkshootvec, Jumpshootvec,
                          Climbshootvec};

    /** @brief Initialize AnimatedObject.
     */
    CharacterAnimate =
        std::make_shared<AnimatedObject>(Idlevec, true, 160, true);
    CharacterAnimate->SetPosition(*Position);
    CharacterAnimate->SetVisible(false);
    CharacterAnimate->SetScale(RightScale);
    CharacterAnimate->SetZIndex(ZIndex);

    /** @brief Initialize ImageObject.
     */

    CharacterImage = std::make_shared<ImageObject>(CharacterImagePath[0]);
    CharacterImage->SetPosition(*Position);
    CharacterImage->SetVisible(false);
    CharacterImage->SetScale(RightScale);
    CharacterImage->SetZIndex(ZIndex);

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
        Death->SetScale(RightScale);
        Death->SetPosition(*Position);
        Death->SetVisible(false);
        CharacterDeath.emplace_back(Death);
    }

    if (CharacterSpawn.empty()) {
        for (int i = 1; i <= 3; i++) {
            std::string path = RESOURCE_DIR "/Picture/Character/Spawn/Initial" +
                               std::to_string(i) + ".png";
            std::shared_ptr<ImageObject> Initial =
                std::make_shared<ImageObject>(path);
            Initial->SetPosition(*Position);
            Initial->SetZIndex(ZIndex);
            Initial->SetScale(RightScale);
            Initial->SetVisible(false);
            CharacterSpawn.emplace_back(Initial);
        }
    }

    /* Switch State */
    RockmanState = LiveState::Spawn;
}

void Rockman::Spawn(std::vector<std::shared_ptr<TileBox>> collison) {
    if (!CharacterSpawn[0]->GetVisibility() && MoveTimer == 0)
        CharacterSpawn[0]->SetVisible(true);
    std::set<RockmanCollison> RockmanCollisonState = GetCollison(collison);
    if (!RockmanCollisonState.count(RockmanCollison::BOTTOM)) {
        for (int i = 0; i < 5; i++) {
            std::set<RockmanCollison> RockmanCollisonState =
                GetCollison(collison);
            if (!RockmanCollisonState.count(RockmanCollison::BOTTOM)) {
                Position->y -= 320 * (Util::Time::GetDeltaTimeMs() / 1000);
                SetPosition(*Position);
                CharacterSpawn[0]->SetPosition(*Position);
            }
            else
                break;
        }
    }
    else {
        for (int i = 0; i <= 2; i++) {
            if (CharacterSpawn[i]->GetVisibility()) {
                switch (i) {
                case 0:
                    CharacterSpawn[1]->SetVisible(true);
                    CharacterSpawn[1]->SetPosition(*Position);
                    CharacterSpawn[0]->SetVisible(false);
                    if (MoveTimer == 0)
                        MoveTimer = Util::Time::GetElapsedTimeMs();
                    break;
                case 1:
                    if (Util::Time::GetElapsedTimeMs() - MoveTimer < 33)
                        break;
                    CharacterSpawn[2]->SetVisible(true);
                    CharacterSpawn[2]->SetPosition(*Position);
                    CharacterSpawn[1]->SetVisible(false);
                    break;
                case 2:
                    if (Util::Time::GetElapsedTimeMs() - MoveTimer < 50)
                        break;
                    Position->y -= 6;
                    CharacterAnimate->SetVisible(true);
                    CharacterAnimate->SetPosition(*Position);
                    CharacterSpawn[2]->SetVisible(false);
                    ColliderBox.clear();
                    ColliderBox.push_back(std::make_shared<Collider>(
                        Position, glm::vec2{18 * 3, 12 * 3}, glm::vec2{0, 18}));
                    ColliderBox.push_back(std::make_shared<Collider>(
                        Position, glm::vec2{18 * 3, 12 * 3},
                        glm::vec2{0, -18}));
                    RockmanState = LiveState::Normal;
                    break;
                }
                break;
            }
        }
    }
}

void Rockman::DoBehavior(std::vector<std::shared_ptr<TileBox>> collison) {
    std::set<RockmanCollison> collisonstate = GetCollison(collison);
    if (Health == 0) {
        RockmanState = LiveState::Death;
    }
    if(Util::Time::GetElapsedTimeMs()-InvincibleTimer>InvincibleTime){
        Invincible = false;
        InvincibleTimer = 0;
    }
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

glm::vec2 Rockman::GetPosition() {
    return *Position;
}

void Rockman::SetPosition(glm::vec2 pos) {
    CharacterAnimate->SetPosition(pos);
    CharacterImage->SetPosition(pos);
    *Position = pos;
}

void Rockman::SetVisable(const int &idx, bool isleft) {
    if (idx == -1) {
        return;
    }

    if (isleft) {
        CharacterAnimate->SetScale(LeftScale);
        CharacterImage->SetScale(LeftScale);
    }
    else {
        CharacterAnimate->SetScale(RightScale);
        CharacterImage->SetScale(RightScale);
    }

    if (MoveState == PhysicState::CLIMB) {
        CharacterAnimate->SetVisible(false);
        CharacterImage->SetVisible(true);
        CharacterImage->SetImage(CharacterImagePath[idx]);
    }
    else if (Visable != idx || MoveState == PhysicState::CLIMBFIN) {
        CharacterAnimate->SetAnimation(CharacterAnimatePath[idx], true, 160,
                                       true);
        CharacterImage->SetVisible(false);
        CharacterAnimate->SetVisible(true);
    }
    Visable = idx;
}

void Rockman::PhysicEngine(std::set<RockmanCollison> collison,
                           std::vector<std::shared_ptr<TileBox>> collisonbox) {
    // TODO: Modify Climb System, Import Shoot.
    Ladder_Pos = {-2000, -2000};
    if (MoveState == PhysicState::MOVE &&
        (!Util::Input::IsKeyPressed(Util::Keycode::RIGHT) &&
         !Util::Input::IsKeyPressed(Util::Keycode::LEFT)))
        SetVisable(0, false);
    if (MoveState == PhysicState::JUMP) {
        Jump(collisonbox);
    }
    if (MoveState == PhysicState::CLIMB) { // Climb if state is climb.
        Climb(collisonbox);
        return;
    }
    glm::vec2 pos = GetPosition();
    if (Util::Input::IsKeyPressed(Util::Keycode::UP) &&
        collison.count(
            RockmanCollison::ROCKMANINLADDER)) // If State isn't Climb and can
                                               // Climb,then climb.
        Climb(collisonbox);
    if (MoveState == Rockman::PhysicState::MOVE) { // Move Left or Right
        if (Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
            SetVisable(1, true);
            for (int i = 0; i < 10; i++) {
                if (collison.count(RockmanCollison::UPLEFT) ||
                    collison.count(RockmanCollison::DOWNLEFT))
                    break;
                pos.x = Util::Time::GetDeltaTimeMs() / 1000 * (-16) + pos.x;
                SetPosition(pos);
            }
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
            SetVisable(1, false);
            for (int i = 0; i < 10; i++) {
                if (collison.count(RockmanCollison::UPRIGHT) ||
                    collison.count(RockmanCollison::DOWNRIGHT))
                    break;
                pos.x = Util::Time::GetDeltaTimeMs() / 1000 * 16 + pos.x;
                SetPosition(pos);
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
        MoveState == PhysicState::JUMPBEFOREMOVE) {
        MoveState = PhysicState::MOVE;
    }
    collison = GetCollison(collisonbox);
    if (MoveState != PhysicState::CLIMB) { // Falling Detect.
        if (MoveState == PhysicState::JUMPBEFOREFALL) {
            MoveState = PhysicState::FALL;
        }
        if (MoveState == PhysicState::MOVE) {
            if (collison.count(RockmanCollison::BOTTEMINLADDER)) {
                if (collison.count(RockmanCollison::ROCKMANINLADDER))
                    MoveState = PhysicState::FALL;
            }
            else if (!collison.count(RockmanCollison::BOTTOM))
                MoveState = PhysicState::FALL;
        }
        if (MoveState == PhysicState::FALL) {
            Fall(collisonbox);
        }
    }
    if (MoveState == PhysicState::CLIMBFIN) { // De-Climbing
        SetPosition({Position->x, Position->y - 48});
        MoveState = PhysicState::MOVE;
    }
    if ((collison.count(RockmanCollison::BOTTOM) &&
         MoveState == PhysicState::JUMPBEFOREFALL)) { // De-Jumping
        if (Visable == 2) {
            if (Util::Input::IsKeyPressed(Util::Keycode::X))
                MoveState = PhysicState::JUMPBEFOREMOVE;
            if (!Util::Input::IsKeyPressed(Util::Keycode::X))
                MoveState = PhysicState::MOVE;
            SetVisable(0, false);
        }
    }
    if (Util::Input::IsKeyPressed(
            Util::Keycode::DOWN)) { // Test, it can't not use when Release.
        if (collison.count(RockmanCollison::BOTTEMINLADDER)) {
            SetPosition({Position->x, Position->y - 16 * 3});
            Climb(collisonbox);
        }
        else {
            // pos.y = Util::Time::GetDeltaTime() * (-160) + pos.y;
            // Setposition(pos);
        }
    }
}

void Rockman::Climb(std::vector<std::shared_ptr<TileBox>> collison) {
    auto CollisonResult = GetCollison(collison);
    if (MoveState != PhysicState::CLIMB) {
        MoveState = PhysicState::CLIMB;
        SetPosition({Ladder_Pos.x, Position->y});
        SetVisable(0, false);
        Ladder_Pos = {-2000, -2000};
    }
    glm::vec2 pos = GetPosition(), initial_yaxis = GetPosition();
    for (int i = 0; i < 10; i++) {
        CollisonResult = GetCollison(collison);
        if (Util::Input::IsKeyPressed(Util::Keycode::UP)) {
            pos.y += 32 * (Util::Time::GetDeltaTimeMs() / 1000);
        }

        if (Util::Input::IsKeyPressed(Util::Keycode::DOWN) &&
            !CollisonResult.count(RockmanCollison::BOTTOM)) {
            pos.y -= 32 * (Util::Time::GetDeltaTimeMs() / 1000);
        }
        else if (Util::Input::IsKeyPressed(Util::Keycode::DOWN) &&
                 CollisonResult.count(RockmanCollison::BOTTOM)) {
            MoveState = PhysicState::CLIMBFIN;
            SetVisable(0, false);
            SetPosition({pos.x, pos.y + 72});
            return;
        }
        if (Util::Input::IsKeyPressed(Util::Keycode::X)) {
            MoveState = PhysicState::FALL;
            SetVisable(2, false);
            return;
        }
        if (!CollisonResult.count(RockmanCollison::ROCKMANINLADDER)) {
            MoveState = PhysicState::CLIMBFIN;
            SetVisable(0, false);
            SetPosition({pos.x, pos.y + 48});
            return;
        }
    }
    if (Util::Time::GetElapsedTimeMs() - ClimbTimer > 250 &&
        pos.y != initial_yaxis.y) {
        if (Visable == 0)
            SetVisable(1, false);
        else
            SetVisable(0, false);
        ClimbTimer = Util::Time::GetElapsedTimeMs();
    }
    CollisonResult = GetCollison(collison);
    SetPosition(pos);
}

void Rockman::Death() {
    if (Visable != -1) {
        Visable = -1;
        CharacterImage->SetVisible(false);
        CharacterAnimate->SetVisible(false);
    }
    if (!CharacterDeath[0]->GetVisibility()) {
        for (int i = 0; i < 12; i++) {
            CharacterDeath[i]->SetPosition(*Position);
            CharacterDeath[i]->SetVisible(true);
        }
    }
    if (CharacterDeath[0]->GetPosition().x > Position->x + 150)
        return;

    int negative = 1;
    for (int i = 0; i < 4; i++) {
        auto delta = Util::Time::GetDeltaTimeMs() / 1000;
        auto position = CharacterDeath[i]->GetPosition();
        if (!(i & 1)) {
            CharacterDeath[i]->SetPosition(
                {position.x + 60 * delta * negative, position.y});
        }
        else {
            CharacterDeath[i]->SetPosition(
                {position.x, position.y + 60 * delta * negative});
            negative *= -1;
        }
    }
    negative = 1;
    for (int i = 4; i < 8; i++) {
        auto delta = Util::Time::GetDeltaTimeMs() / 1000;
        auto position = CharacterDeath[i]->GetPosition();
        if (!(i & 1)) {
            CharacterDeath[i]->SetPosition(
                {position.x + 120 * delta * negative, position.y});
        }
        else {
            CharacterDeath[i]->SetPosition(
                {position.x, position.y + 120 * delta * negative});
            negative *= -1;
        }
    }
    int negative_x = 1, negative_y = 1;
    for (int i = 8; i < 12; i++) {
        auto delta = Util::Time::GetDeltaTimeMs() / 1000;
        auto position = CharacterDeath[i]->GetPosition();
        if (!(i & 1)) {
            CharacterDeath[i]->SetPosition(
                {position.x + 86.6 * delta * negative_x,
                 position.y + 86.6 * delta * negative_y});
            negative_x *= -1;
        }
        else {
            CharacterDeath[i]->SetPosition(
                {position.x + 86.6 * delta * negative_x,
                 position.y + 86.6 * delta * negative_y});
            negative_y *= -1;
        }
    }
}

int Rockman::GetHealth() {
    return Health;
}
void Rockman::SetHealth(int hp) {
    if (hp < 0 || hp > 28)
        return;
    Health = hp;
    if (Health == 0) {
        RockmanState = LiveState::Death;
    }
}

void Rockman::Shoot() {
    if (Util::Input::IsKeyDown(Util::Keycode::Z)) {
        SetShootVisable(Visable, true);
        if (MoveState == PhysicState::MOVE)
            MoveState = PhysicState::SHOOT;
        glm::vec2 ammo_position = {Position->x + 35, Position->y + 5};
        glm::vec2 direction = {-480, 0};
        bool IsLeft = Util::Input::IsKeyPressed(Util::Keycode::LEFT);
        if (!IsLeft) {
            direction.x = 480;
        }
        std::shared_ptr<Ammo> ammo = std::make_shared<Ammo>(
            ammo_position, direction,
            RESOURCE_DIR "/Picture/Character/Shooting/Ammo.png",
            glm::vec2{8 * 3, 8 * 3}, AmmoType::ROCKMAN);
        Magazine.push_back(ammo);
        ShootTimer = Util::Time::GetElapsedTimeMs();
        return;
    }
    if (Util::Time::GetElapsedTimeMs() - ShootTimer > 100 && ShootTimer != 0) {
        SetShootVisable(Visable, false);
        if (MoveState == PhysicState::SHOOT)
            MoveState = PhysicState::MOVE;
        ShootTimer = 0;
    }
}
void Rockman::SetShootVisable(const int &idx, bool visable) {
    if (MoveState == PhysicState::CLIMB) {
        if (visable == true)
            CharacterImage->SetImage(CharacterShootPath[3]);
        else
            CharacterImage->SetImage(CharacterImagePath[0]);
    }
    else {
        CharacterAnimate->SetVisible(!visable);
        CharacterImage->SetVisible(visable);
        CharacterImage->SetImage(CharacterShootPath[idx]);
    }
    if (Util::Input::IsKeyPressed(Util::Keycode::LEFT))
        CharacterImage->SetScale(LeftScale);
    else
        CharacterImage->SetScale(RightScale);
}
std::set<Rockman::RockmanCollison>
Rockman::GetCollison(std::vector<std::shared_ptr<TileBox>> collison) {
    std::set<RockmanCollison> box;
    for (int i = 0; i < collison.size(); i++) {
        Collider rockmanup = *ColliderBox[0], rockmandown = *ColliderBox[1];
        if (collison[i]->GetObjectType() == TileBox::ObjectType::CLIMB) {
            if (IsColliding(rockmandown, *(collison[i]->Getcollisonbox()))) {
                bool OverLap = IfObjectIsOverlaping(
                    rockmandown, *(collison[i]->Getcollisonbox()));
                auto CollisonResult = WhereIsColliding(
                    rockmandown, *(collison[i]->Getcollisonbox()));
                if (OverLap) {
                    if (glm::vec2{-2000, -2000} == Ladder_Pos) {
                        Ladder_Pos = collison[i]->GetPosition();
                    }
                    box.insert(RockmanCollison::ROCKMANINLADDER);
                }
                if (CollisonResult.count(Collider::Bound::BOTTOM)) {
                    box.insert(RockmanCollison::BOTTEMINLADDER);
                }
            }
            continue;
        }
        auto collisonresult =
            WhereIsColliding(rockmanup, *(collison[i]->Getcollisonbox()));
        if (collisonresult.count(Collider::Bound::TOP))
            box.insert(RockmanCollison::TOP);
        if (collisonresult.count(Collider::Bound::LEFT))
            box.insert(RockmanCollison::UPLEFT);
        if (collisonresult.count(Collider::Bound::RIGHT))
            box.insert(RockmanCollison::UPRIGHT);
        collisonresult =
            WhereIsColliding(rockmandown, *(collison[i]->Getcollisonbox()));
        if (collisonresult.count(Collider::Bound::LEFT))
            box.insert(RockmanCollison::DOWNLEFT);
        if (collisonresult.count(Collider::Bound::RIGHT))
            box.insert(RockmanCollison::DOWNRIGHT);
        if (collisonresult.count(Collider::Bound::BOTTOM))
            box.insert(RockmanCollison::BOTTOM);
    }
    return box;
}

Rockman::LiveState Rockman::GetCurrentState() {
    return RockmanState;
}

std::vector<std::shared_ptr<Util::GameObject>> Rockman::GetAllChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> Object;
    Object.push_back(CharacterAnimate);
    Object.push_back(CharacterImage);
    for (auto i : CharacterDeath)
        Object.push_back(i);
    for (auto i : CharacterSpawn)
        Object.push_back(i);
    return Object;
}
void Rockman::Jump(std::vector<std::shared_ptr<TileBox>> collison) {
    glm::vec2 pos = *Position;
    auto result = GetCollison(collison);
    if (MoveState == PhysicState::FALL ||
        MoveState == PhysicState::JUMPBEFOREFALL)
        return;
    if (MoveState != PhysicState::JUMP) {
        if (result.count(RockmanCollison::TOP))
            return;
        MoveState = PhysicState::JUMP;
        Initial_Pos = pos;
        SetVisable(2, false);
        SetPosition(pos);
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
                    pos.x += 16 * (Util::Time::GetDeltaTimeMs() / 1000);
                    SetVisable(2, false);
                }
                if (!result.count(RockmanCollison::DOWNLEFT) &&
                    !result.count(RockmanCollison::UPLEFT) &&
                    Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
                    pos.x -= 16 * (Util::Time::GetDeltaTimeMs() / 1000);
                    SetVisable(2, true);
                }
                pos.y += 120 * (Util::Time::GetDeltaTimeMs() / 1000);
                SetPosition(pos);
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
        glm::vec2 pos = *Position;
        falltimer = Util::Time::GetElapsedTimeMs();
        for (int i = 0; i < 6; i++) {
            auto result = GetCollison(collison);
            bool CanFall = (!result.count(RockmanCollison::BOTTOM) &&
                            !result.count(RockmanCollison::BOTTEMINLADDER)) ||
                           (result.count(RockmanCollison::BOTTEMINLADDER) &&
                            result.count(RockmanCollison::ROCKMANINLADDER));
            if (CanFall) {
                bool isleft = false;
                pos.y -= 60 * (Util::Time::GetDeltaTimeMs() / 1000);
                if (!result.count(RockmanCollison::DOWNRIGHT) &&
                    !result.count(RockmanCollison::UPRIGHT) &&
                    Util::Input::IsKeyPressed(Util::Keycode::RIGHT)) {
                    pos.x += 32 * (Util::Time::GetDeltaTimeMs() / 1000);
                }
                if (!result.count(RockmanCollison::DOWNLEFT) &&
                    !result.count(RockmanCollison::UPLEFT) &&
                    Util::Input::IsKeyPressed(Util::Keycode::LEFT)) {
                    pos.x -= 32 * (Util::Time::GetDeltaTimeMs() / 1000);
                    isleft = true;
                }
                SetPosition(pos);
                SetVisable(2, isleft);
            }
            else {
                if (MoveState == PhysicState::FALL)
                    MoveState = PhysicState::MOVE;
                else
                    MoveState = PhysicState::JUMPBEFOREMOVE;
                SetVisable(0, false);
                falltimer = 0;
            }
        }
    }
}

bool Rockman::GetInvincible() {
    return Invincible;
}
void Rockman::SetInvincible() {
    if(Invincible) return;
    Invincible = true;
    InvincibleTimer = Util::Time::GetElapsedTimeMs();
}

void Rockman::DebugMessageCollidor(std::set<RockmanCollison> collidorstate,
                                   std::string locate) {
    LOG_DEBUG("=========" + locate + "============");
    for (auto test : collidorstate) {
        switch (test) {
        case RockmanCollison::UPRIGHT:
            LOG_INFO("UPRIGHT");
            break;
        case RockmanCollison::UPLEFT:
            LOG_INFO("UPLEFT");
            break;
        case RockmanCollison::TOP:
            LOG_INFO("TOP");
            break;
        case RockmanCollison::BOTTOM:
            LOG_INFO("BOTTOM");
            break;
        case RockmanCollison::DOWNRIGHT:
            LOG_INFO("DOWNRIGHT");
            break;
        case RockmanCollison::DOWNLEFT:
            LOG_INFO("DOWNLEFT");
            break;
        case RockmanCollison::BOTTEMINLADDER:
            LOG_INFO("BOTTEMINLADDER");
            break;
        case RockmanCollison::ROCKMANINLADDER:
            LOG_INFO("ROCKMANINLADDER");
            break;
        }
    }
    LOG_INFO("=====================");
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
