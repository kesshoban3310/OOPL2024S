#ifndef BLASTER_HPP
#define BLASTER_HPP

#include "Component/Ammo.hpp"
#include "Component/Collider.hpp"
#include "Component/EnemyAttribute.hpp"
#include "Component/ImageObject.hpp"
#include "pch.hpp"

// 4896 -2832
class Blaster : public Enemy, Shootable {
public:
    Blaster(glm::vec2 pos, glm::vec2 collidersize, glm::vec2 scale,
            unsigned long animationinterval, bool increase,
            std::vector<std::string> path, std::string ammopath, int health,
            bool visable, Enemy::HurtState hurtstate,
            Enemy::LifeState lifestate);
    void DoBehavior(glm::vec2 position) override;
    void Shoot() override;

    [[nodiscard]] std::vector<std::shared_ptr<Ammo>> Getammo() {
        auto Object = magazine;
        magazine.clear();
        return Object;
    }

private:
    std::vector<std::string> Path;
    std::string AmmoPath;
    std::vector<std::shared_ptr<Ammo>> magazine;
    unsigned long AnimationTimer = 0, AnimationInterval;
    int AnimationCount = 0;
    int PathIndex = 0;
    bool Open = 1;
};

#endif
