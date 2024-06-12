#ifndef BOMBOMBOMB_HPP
#define BOMBOMBOMB_HPP

#include "Component/Ammo.hpp"
#include "Component/Collider.hpp"
#include "Component/EnemyAttribute.hpp"
#include "Component/Bomb.hpp"
#include "ImageObject.hpp"
#include "Util/Time.hpp"
#include "glm/fwd.hpp"
#include <cmath>
#include <memory>
#include <string>
#include <vector>

class Bombombomb : public Enemy, Physic {
public:
    Bombombomb(glm::vec2 pos, glm::vec2 speed, glm::vec2 ammospeed,
               glm::vec2 scale, glm::vec2 colldiersize, std::string path,
               std::string ammopath, int health, bool visable,
               Enemy::HurtState hurtState);
    void DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) override;
    void PhysicEngine() override;
    void Split();
    void Reset() override;
    [[nodiscard]] std::vector<std::shared_ptr<Bomb>> GetBombs() {
        std::vector<std::shared_ptr<Bomb>> SmallBombObject = SmallBomb;
        SmallBomb.clear();
        return SmallBombObject;
    }
private:
    std::vector<std::shared_ptr<Bomb>> SmallBomb;
    std::string Path;
    std::string AmmoPath;
    glm::vec2 InitialPosition, FinalPosition;
    glm::vec2 Speed, AmmoSpeed;
    float WaitingCounter = 0;
    bool BeSmallBomb;
};
#endif
