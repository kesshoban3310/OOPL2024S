#ifndef ROCKMAN_HPP
#define ROCKMAN_HPP

#include "Component/AnimatedObject.hpp"
#include "pch.hpp"
#include "Ammo.hpp"
#include "Component/Healthbar.hpp"
#include "Component/Collider.hpp"
#include "Component/TileBox.hpp"
#include "Util/Logger.hpp"
#include <queue>


class Rockman {
private:
    enum class RockmanCollison{
        TOP,
        BOTTOM,
        UPLEFT,
        UPRIGHT,
        DOWNLEFT,
        DOWNRIGHT,
        ROCKMANINLADDER,
        BOTTEMINLADDER,
    };
public:
    enum class PhysicState{
        JUMP,
        CLIMB,
        SHOOT,
        MOVE,
        FALL,
        JUMPBEFOREMOVE,
        JUMPBEFOREFALL,
        CLIMBFIN,
    };
    enum class LiveState{
        Spawn,
        Initial,
        Normal,
        Death,
    };
    /**
     * @brief Constructor.
     */
    Rockman(glm::vec2 pos,LiveState Rockmanstate);

    /**
     * @brief Rockman's all behavior, move 、 shoot or other.
     * A helper to choose what Rockman need to do now.
     */
    void Behavior(std::vector<std::shared_ptr<TileBox>> collison);

    /**
     * @brief Set object position.
     */
    void Setposition(glm::vec2 pos);

    /**
     * @brief Get Rockman's health.
     * @return Rockman's health.
     */
    int Gethealth();

    /**
     * @brief Get object position.
     * @return Object's postition.
     */
    glm::vec2 Getposition();

    LiveState Getcurrentstate();
    /**
     * @brief collect all object in character.
     * @return All object in character.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetAllchildren();
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> Getchildren(LiveState state);
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> Gethealthbar(){ return healthbar->GetChildren(); };
    [[nodiscard]] std::vector<std::shared_ptr<Ammo>> Getammo(){
        auto Object = magazine;
        magazine.clear();
        return Object;
    }
    [[nodiscard]] std::shared_ptr<Healthbar> GetHealthbar(){ return healthbar;}  // Need 封裝
    [[nodiscard]] std::vector<std::shared_ptr<Collider>> GetCollider(){return collider;}

private:
    /**
     * @brief Initialize the object.
     * Include all Image into this class.
     */
    void Initialize();

    /**
     * @brief Spawn animation for Rockman into map.
     * Drop it to the point.
     */

    void Spawn(std::vector<std::shared_ptr<TileBox>> collison);

    /**
     * @brief Rockman's all moving action.
     */
    void PhysicEngine(std::set<Rockman::RockmanCollison> collison,std::vector<std::shared_ptr<TileBox>> collisonbox);

    /**
     * @brief Rockman's shoot animation.
     */
    void Shoot();

    /**
     * @brief Rockman's death animation.
     */
    void Death();

    /**
     * @brief Set Rockman's health.
     * @param health for Rockman's health.
     */
    void Sethealth(int hp);

    /**
     * @brief Set Object different movement.
     * @param idx for the character's index.
     */
    void Setvisable(const int &idx);

    /**
     * @brief Set Object different movement.
     * @param idx for the character's index.
     * @param visable for shoot object can see.
     */
    void Setshootvisable(const int &idx,bool visable);

    //TODO: Re-format GetCollison when Collider is re-format.
    /**
     * @brief Judge where Rockman is collide.
     * @param collison for foreobject.
     * @return Rockman collide state.
     */
    std::set<RockmanCollison> GetCollison(std::vector<std::shared_ptr<TileBox>> collison);

    /**
     * @brief Rockman's Jumping Animation.
     * @param collison for foreobject.
     */
    void Jump(std::vector<std::shared_ptr<TileBox>> collison);
    unsigned long jumptimer = 0;

    /**
     * @brief Rockman's Falling Animation.
     * @param collison for foreobject.
     */
    void Fall(std::vector<std::shared_ptr<TileBox>> collison);
    unsigned long falltimer = 0;

    /**
     * @brief Rockman's Climbing Animation.
     * @param collison for foreobject.
     */
    void Climb(std::vector<std::shared_ptr<TileBox>> collison);

    /**
     * @brief Print LOG_DEBUG for rockman's collison state.
     * @param collidorstate for a set storing Rockman's collison state.
     * @param locate for where the function call or other message.
     */
    void DebugMessageCollidor(std::set<Rockman::RockmanCollison> collidorstate,std::string locate);

    /**
     * @brief Print LOG_DEBUG for rockman's physic state.
     * @param physicState for a variable storing Rockman's physic state.
     */
    void DebugMessagePhysic(Rockman::PhysicState physicState);

    std::vector<std::shared_ptr<AnimatedObject>> character;
    std::vector<std::shared_ptr<AnimatedObject>> character_shoot;
    std::vector<std::shared_ptr<AnimatedObject>> character_death;
    std::vector<std::shared_ptr<ImageObject>> character_spawn;
    std::vector<std::shared_ptr<Ammo>> magazine;

    // timer to make animation smoothly.
    unsigned long movetimer = 0,shoottimer = 0;
    int health = 28;
    int visable = 0;

    std::shared_ptr<glm::vec2> position;
    glm::vec2 scale = {3,3},inversescale = {-3,3};
    float ZIndex = 70;

    glm::vec2 Initial_Pos = {-1,-1}; //when Using Jumping module, to calculate the moving.
    glm::vec2 Ladder_Pos = {-2000,-2000};
    LiveState RockmanState;
    PhysicState MoveState;

    std::vector<std::shared_ptr<Collider>> collider;
    std::shared_ptr<Healthbar> healthbar;
};
#endif
