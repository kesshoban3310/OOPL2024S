#ifndef KILLER_BOMB_HPP
#define KILLER_BOMB_HPP

#include "Component/EnemyAttribute.hpp"
#include "Component/ImageObject.hpp"
#include "Component/Collider.hpp"
#include "Util/Time.hpp"
#include <memory>
#include <cmath>

class KillerBomb:public Enemy,Physic{
public:
    KillerBomb(glm::vec2 inipos,glm::vec2 speed,glm::vec2 scale,std::string path,int health,bool visable);
    void DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) override;
    void PhysicEngine() override;

    void SetHealth(int health);
    int GetHealth();

    void SetVisable(bool visable);
    bool GetVisable();
private:
    long long CoolDownTimer = 0,CoolDownTime = 500;




    std::string Path;
    glm::vec2 Scale;
    glm::vec2 Speed;
    int Theta = 0;
};

#endif
