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
    Blaster(glm::vec2 pos, unsigned long animationinterval, bool increase);
    void Behavior(glm::vec2 position) override;
    void Initialize() override;
    void Shoot() override;
    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() {
        std::shared_ptr<Util::GameObject> child = Object;
        return child;
    }
    [[nodiscard]] std::vector<std::shared_ptr<Ammo>> Getammo() {
        auto Object = magazine;
        magazine.clear();
        return Object;
    }

private:
    std::shared_ptr<ImageObject> Object;
    std::vector<std::string> ObjectPath;
    std::shared_ptr<Collider> Collibox;
    std::shared_ptr<glm::vec2> position;
    std::vector<std::shared_ptr<Ammo>> magazine;
    unsigned long AnimationTimer = 0, AnimationInterval;
    int AnimationCount = 0;
    int PathIndex = 0;
    bool Open = 1;
    std::string AmmoPath;
};

#endif
