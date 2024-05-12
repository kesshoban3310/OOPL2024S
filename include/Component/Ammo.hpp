#ifndef AMMO_HPP
#define AMMO_HPP

#include "Component/Collider.hpp"
#include "ImageObject.hpp"
#include "pch.hpp"

enum class AmmoType { ROCKMAN, ENEMY };

class Ammo {
public:
    Ammo(glm::vec2 position, glm::vec2 speed, std::string imagepath,
         glm::vec2 ammosize, AmmoType type);
    void Behavior();
    bool Outofrange(glm::vec2 camerapos);
    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() {
        std::shared_ptr<Util::GameObject> Object = ammo;
        return Object;
    }

    [[nodiscard]] Collider GetCollider() { return *colliderbox; }

    [[nodiscard]] AmmoType GetAmmoType() { return type; }

    void MarkForRemoval() { marked_for_removal = true; }

    [[nodiscard]] bool IsMarkedForRemoval() const { return marked_for_removal; }

private:
    std::shared_ptr<ImageObject> ammo;
    std::shared_ptr<Collider> colliderbox;
    std::shared_ptr<glm::vec2> initial_position;
    glm::vec2 final_position;
    glm::vec2 speed;
    std::string path;
    double delta;
    bool marked_for_removal = false;
    AmmoType type;
};

#endif
