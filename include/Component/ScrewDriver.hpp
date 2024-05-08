#ifndef SCREW_DRIVER_HPP
#define SCREW_DRIVER_HPP

#include "Component/Ammo.hpp"
#include "Component/Collider.hpp"
#include "Component/EnemyAttribute.hpp"
#include "Component/ImageObject.hpp"

// 4896 -2832
class Screwdriver : public Enemy, Shootable {
public:
    Screwdriver(glm::vec2 pos);
    void Behavior(glm::vec2 pos) override;
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
    unsigned long AnimationTimer = 0, AnimationInterval = 60;
    int AnimationCount = 0;
    bool Open = 0, StartUp = 0;
    int PathIndex = 0;
};

#endif
