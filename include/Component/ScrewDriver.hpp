#ifndef SCREW_DRIVER_HPP
#define SCREW_DRIVER_HPP

#include "Component/Ammo.hpp"
#include "Component/Collider.hpp"
#include "Component/EnemyAttribute.hpp"
#include "Component/ImageObject.hpp"

// 4896 -2832
class Screwdriver : public Enemy, Shootable {
public:
    Screwdriver(glm::vec2 pos, glm::vec2 scale, glm::vec2 collidersize,
                std::vector<std::string> path, std::string ammopath,
                Enemy::LifeState lifestate, Enemy::HurtState hurtstate,
                int health, bool visable);
    void DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                    int SceneStage) override;
    void Shoot() override;
    void Reset() override;
    [[nodiscard]] std::vector<std::shared_ptr<Ammo>> GetAmmo() {
        auto Object = Magazine;
        Magazine.clear();
        return Object;
    }

private:
    std::vector<std::string> ObjectPath;
    std::string AmmoPath;
    std::vector<std::shared_ptr<Ammo>> Magazine;

    // Deal Animation of ScrewDriver.
    float AnimationTimer = 0, AnimationInterval = 80;
    int AnimationCount = 0;
    bool Open = 0, StartUp = 0;
    int PathIndex = 0;
};

#endif
