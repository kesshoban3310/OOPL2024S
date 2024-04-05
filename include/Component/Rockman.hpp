#ifndef ROCKMAN_HPP
#define ROCKMAN_HPP

#include "AnimatedObject.hpp"
#include "pch.hpp"
#include "Ammo.hpp"
#include "Component/Healthbar.hpp"
#include "Component/Collider.hpp"
#include <queue>


class Rockman {
public:
    enum class State{
        Spawn,
        Initial,
        Normal,
        Death,
    };
    /**
     * @brief Constructor.
     */
    Rockman(glm::vec2 pos,State Rockmanstate);
    /**
     * @brief Initialize the object.
     * Include all Image into this class.
     */
    void Initialize();

    /**
     * @brief Spawn Rockman to map.
     * Drop it to the point.
     */

    void Spawn();

    /**
     * @brief Rockman's all behavior, move 、 shoot or other.
     * A helper to choose what Rockman need to do now.
     */
    void behavior();

    /**
     * @brief Rockman's all move.
     */
    void move();

    /**
     * @brief Rockman's shoot animation.
     */
    void shoot();
    /**
     * @brief Rockman's death animation.
     */
    void death();
    /**
     * @brief Get Rockman's health.
     * @return Rockman's health.
     */
    int Gethealth();
    /**
     * @brief Set Rockman's health.
     * @param hp for Rockman's health.
     */
    void Sethealth(int hp);

    /**
     * @brief Set object position.
     */
    void Setposition(glm::vec2 pos);

    /**
     * @brief Get object position.
     * @return Object's postition.
     */
    glm::vec2 Getposition();

    /**
     * @brief Set Object different movement.
     * @param idx for the character's index.
     */
    void Setvisable(const int &idx);

    State Getcurrentstate();
    /**
     * @brief collect all object in character.
     * @return All object in character.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetAllchildren();
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> Getchildren(State state) ;
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> Gethealthbar(){ return healthbar->GetChildren(); };
    [[nodiscard]] std::vector<std::shared_ptr<Ammo>> Getammo(){
        auto Object = magazine;
        magazine.clear();
        return Object;
    }
    [[nodiscard]] std::shared_ptr<Healthbar> GetHealthbar(){ return healthbar;}  // Need 封裝
    [[nodiscard]] std::vector<std::shared_ptr<Collider>> GetCollider(){return collider;}
private:
    std::vector<std::shared_ptr<AnimatedObject>> character;
    std::vector<std::shared_ptr<AnimatedObject>> character_shoot;
    std::vector<std::shared_ptr<AnimatedObject>> character_death;
    std::vector<std::shared_ptr<ImageObject>> character_spawn;
    std::vector<std::shared_ptr<Ammo>> magazine;
    // timer to make animation smoothly.
    unsigned long movetimer = -1,shoottimer = -1;
    int health = 28;
    int visable = 0;

    std::shared_ptr<glm::vec2> position;
    glm::vec2 scale = {3,3},inversescale = {-3,3};
    float ZIndex = 70;

    glm::vec2 initial_pos = {-1,-1}; //when Using Jumping module, to calculate the moving.
    State Rockmanstate;
    void Setshootvisable(const int &idx,bool visable);
    bool is_jumping = 0,is_falling = 0;
    double speed = 20.0,acclerator = 10.0,power = 175.0;
    int Jump_bar = -1;
    std::vector<std::shared_ptr<Collider>> collider;
    std::shared_ptr<Healthbar> healthbar;
};
#endif
