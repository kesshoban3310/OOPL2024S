#ifndef ENEMY_ATTRIBUTE_HPP
#define ENEMY_ATTRIBUTE_HPP

#include "Component/Collider.hpp"
#include "Component/ImageObject.hpp"
#include "Util/GameObject.hpp"
#include "glm/vec2.hpp"
#include "pch.hpp"
#include <memory>

/**
 * @brief This class is an object pool for every enemy man.
 * Including and inherit the attribute you want.
 */
class Enemy {
public:
    enum class HurtState { // To see if it is harmful or unharmful.
        INVINCIBLE,        // Unharmful.
        COWARDLY,          // Harmful.
    };
    enum class LifeState { // To see if it is life or dead.
        LIFE,
        DEAD,
    };
    Enemy(glm::vec2 pos, std::string path, int hp, bool visable,
          glm::vec2 collidersize, HurtState state,
          LifeState lifeState = LifeState::LIFE, glm::vec2 scale = {3, 3});
    virtual ~Enemy() = default;
    virtual void Behavior(glm::vec2 position) = 0;

    virtual glm::vec2 GetPosition();
    virtual void SetPosition(glm::vec2 pos);

    virtual void SetHealth(int health);
    virtual int GetHealth();

    virtual void SetVisable(bool visable); // disable enemy.
    virtual bool GetVisable();             // Get Visable

    virtual void SetImage(std::string path);

    virtual HurtState GetHurtState();
    virtual void SetHurtState(HurtState hurtstate);

    virtual LifeState GetLifeState();
    virtual void SetLifeState(LifeState lifestate);

    [[nodiscard]] Collider GetCollider() {
        return *Hitbox;
    } // Get Enemy Collider.
    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild() {
        std::shared_ptr<Util::GameObject> object = Object;
        return object;
    }

protected:
    std::shared_ptr<ImageObject> Object;
    std::shared_ptr<glm::vec2> Position;
    std::shared_ptr<Collider> Hitbox;
    HurtState Hurt;
    glm::vec2 Scale;
    int Health;
    bool Visable;
    LifeState Life;
};

class Attackable {
public:
    virtual void Attack() = 0;
};
class Physic {
public:
    virtual void PhysicEngine() = 0;
};
class Shootable {
public:
    virtual void Shoot() = 0;
};

#endif
