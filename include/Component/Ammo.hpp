#ifndef AMMO_HPP
#define AMMO_HPP

#include "Component/Collider.hpp"
#include "ImageObject.hpp"
#include "pch.hpp"

class Ammo {
public:
    Ammo(glm::vec2 position, glm::vec2 speed, std::string imagepath,
         glm::vec2 ammosize);
    void Behavior();
    bool Outofrange(glm::vec2 camerapos);
    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() {
        std::shared_ptr<Util::GameObject> Object = ammo;
        return Object;
    }

private:
    std::shared_ptr<ImageObject> ammo;
    std::shared_ptr<Collider> colliderbox;
    std::shared_ptr<glm::vec2> initial_position;
    glm::vec2 final_position;
    glm::vec2 speed;
    std::string path;
    double delta;
};

#endif
