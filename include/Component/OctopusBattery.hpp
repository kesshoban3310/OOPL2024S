#ifndef OCTOPUS_BATTERY_HPP
#define OCTOPUS_BATTERY_HPP

#include "Component/EnemyAttribute.hpp"
#include "Component/ImageObject.hpp"
#include "Component/Collider.hpp"
#include "pch.hpp"

class OctopusBattery:public Enemy,Physic{
public:
    enum class OctopusState{
        SLEEP,
        BLEAZY,
        AWAKE,
    };
    OctopusBattery(glm::vec2 inipos,glm::vec2 finpos,glm::vec2 speed,glm::vec2 scale,std::vector<std::string> path,OctopusState state);
    void Behavior(glm::vec2 position) override;
    void Initialize() override;
    void PhysicEngine() override;
    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild(){
        std::shared_ptr<Util::GameObject> GameObject = Object;
        return GameObject;
    }
private:
    std::vector<std::string> Path;
    std::shared_ptr<ImageObject> Object;
    std::shared_ptr<Collider> CollisonBox;
    std::shared_ptr<glm::vec2> Position;
    glm::vec2 InitialPosition,FinalPosition;
    glm::vec2 Speed;
    glm::vec2 Scale;
    OctopusBattery::OctopusState State;
    float SleepCounter,BleazyCounter;
};
#endif