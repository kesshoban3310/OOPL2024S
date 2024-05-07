#ifndef BOMBOMBOMB_HPP
#define BOMBOMBOMB_HPP

#include "ImageObject.hpp"
#include "Component/EnemyAttribute.hpp"
#include "Component/Ammo.hpp"
#include "Component/Collider.hpp"
#include "glm/fwd.hpp"
#include "Util/Time.hpp"
#include <vector>
#include <memory>
#include <string>
#include <cmath>

class Bombombomb:Enemy,Physic{
public:
    Bombombomb(glm::vec2 pos,glm::vec2 speed,glm::vec2 ammospeed,glm::vec2 scale,std::string path,std::string ammopath);
    void Initialize() override;
    void Behavior(glm::vec2 position) override;
    void PhysicEngine() override;
    void Split();
    void SmallBombMove();
    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() {return Object;}
    [[nodiscard]] glm::vec2 GetPosition(){return *Position;}
    [[nodiscard]] Collider GetCollider(){return *Collisonbox;}
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetAmmos() {
        std::vector<std::shared_ptr<Util::GameObject>> SmallBombObject;
        for(auto i:SmallBomb)
            SmallBombObject.push_back(i);
        return SmallBombObject;
    }
private:
    std::shared_ptr<ImageObject> Object;
    std::vector<std::shared_ptr<ImageObject>> SmallBomb;
    std::shared_ptr<Collider> Collisonbox;
    std::shared_ptr<glm::vec2> Position;
    std::string Path;
    std::string AmmoPath;
    glm::vec2 InitialPosition,FinalPosition;
    glm::vec2 Scale;
    glm::vec2 Speed,AmmoSpeed;
    float WaitingCounter = 0;
    bool BeSmallBomb;
};
#endif
