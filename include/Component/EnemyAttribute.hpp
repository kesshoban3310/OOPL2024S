#ifndef ENEMY_ATTRIBUTE_HPP
#define ENEMY_ATTRIBUTE_HPP

#include "glm/vec2.hpp"
#include "pch.hpp"
#include "Util/GameObject.hpp"

/**
 * @brief This class is an object pool for every enemy man.
 * Including and inherit the attribute you want.
 */
class Enemy{
public:
    virtual void Behavior(glm::vec2 position) = 0;
    virtual void Initialize() = 0;
};
class Attackable {
public:
    virtual void Attack() = 0;
};
class Physic{
public:
    virtual void PhysicEngine() = 0;
};
class Shootable{
public:
    virtual void Shoot() = 0;
};
#endif
