#ifndef MAMBU_HPP
#define MAMBU_HPP

#include "Component/Ammo.hpp"
#include "Component/Collider.hpp"
#include "Component/EnemyAttribute.hpp"
#include "Component/ImageObject.hpp"
#include "Util/Time.hpp"
#include <cmath>

class Mambu : public Enemy, Physic, Shootable {
public:
    Mambu(glm::vec2 pos, std::vector<std::string> path, glm::vec2 speed,
          glm::vec2 ammospeed, std::string ammopath, glm::vec2 collidersize,
          int health, bool visable);
    void DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                    int SceneStage) override;
    void PhysicEngine() override;
    void Shoot() override;

    [[nodiscard]] glm::vec2 GetPosition() { return *Position; }
    [[nodiscard]] std::vector<std::shared_ptr<Ammo>> GetAmmo() {
        return Magazine;
    }
    [[nodiscard]] Collider GetCollider() { return *Hitbox; }
    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() {
        std::shared_ptr<Util::GameObject> object = Object;
        return object;
    }

private:
    std::vector<std::string> Path;
    glm::vec2 Speed, AmmoSpeed;
    std::string AmmoPath;
    int Health;
    std::vector<std::shared_ptr<Ammo>> Magazine;
    float AnimationTimer = 0;
    float CircumlateX = 0, DiffWithCamX = 0;
};

#endif
