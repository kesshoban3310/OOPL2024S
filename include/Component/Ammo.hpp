#ifndef AMMO_HPP
#define AMMO_HPP

#include "ImageObject.hpp"
#include "pch.hpp"

class Ammo {
public:
    Ammo(glm::vec2 position, int direction);
    void Behavior();
    bool Outofrange();
    [[nodiscard]] std::shared_ptr<Util::GameObject> Getchild() {
        std::shared_ptr<Util::GameObject> Object = ammo;
        return Object;
    }

private:
    std::shared_ptr<ImageObject> ammo;
    glm::vec2 initial_position;
    glm::vec2 final_position;
    double delta;
};

#endif
