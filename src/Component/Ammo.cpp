//
// Created by User on 2024/3/22.
//
#include "Component/Ammo.hpp"
#include "Util/Time.hpp"


Ammo::Ammo(glm::vec2 position,int direction){
    ammo = std::make_shared<ImageObject>(RESOURCE_DIR "/Picture/Character/Shooting/Ammo.png");
    initial_position = position;
    ammo->SetPosition(initial_position);
    ammo->SetScale({3,3});
    ammo->SetZIndex(3);
    ammo->SetVisible(true);
    if(!direction){ // east
        final_position = {position.x-720,position.y};
        delta = -1;
    }
    else  { //west
        final_position = {position.x+720,position.y};
        delta = 1;
    }
}
bool Ammo::Outofrange() { // need to add collision box;
    if(delta == 1)
        return initial_position.x >= final_position.x;
    else
        return initial_position.x <= final_position.x;
}
void Ammo::Behavior() {
    initial_position.x += (1/Util::Time::GetDeltaTime())*delta*0.1;
    ammo->SetPosition(initial_position);
}
