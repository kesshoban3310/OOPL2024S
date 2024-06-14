#ifndef ROCKMAN_HPP
#define ROCKMAN_HPP

#include "Component/AnimatedObject.hpp"
#include "pch.hpp"
#include "Ammo.hpp"
#include "Component/Collider.hpp"
#include "Component/TileBox.hpp"
#include "Util/Logger.hpp"
#include "Util/SFX.hpp"
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
        WaitSpawn,
        WAITREVIVAL,
        FROZEN,
    };
    /**
     * @brief Constructor.
     */
    Rockman(glm::vec2 pos,LiveState Rockmanstate);

    /**
     * @brief Rockman's all behavior, move 、 shoot or other.
     * A helper to choose what Rockman need to do now.
     */
    void DoBehavior(std::vector<std::shared_ptr<TileBox>> collison);

    /**
     * @brief Set object position.
     */
    void SetPosition(glm::vec2 pos);

    /**
     * @brief Get Rockman's health.
     * @return Rockman's health.
     */
    int GetHealth();

    /**
     * @brief Get object position.
     * @return Object's postition.
     */
    glm::vec2 GetPosition();

    /**
     * @brief Set Rockman's health.
     * @param health for Rockman's health.
     */
    void SetHealth(int hp);
    /**
     * @brief Get Rockman's LiveState.
     * @param health for Rockman's health.
     */
    LiveState GetCurrentState();
    /**
     * @brief Set Rockman to Invincible.
     */
    void SetInvincible();

    /**
     * @brief Get if Rockman is Invincible.
     */
    bool GetInvincible();

    /**
     * @brief Set Debug mode.
     */
    void SetRockmanDebugMode();
    void Revival();
    void SetLifeState(Rockman::LiveState livestate);
    /**
     * @brief collect all object in character.
     * @return All object in character.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetAllChildren();
    [[nodiscard]] std::vector<std::shared_ptr<Ammo>> GetAmmo(){
        auto Object = Magazine;
        Magazine.clear();
        return Object;
    }
    [[nodiscard]] std::vector<std::shared_ptr<Collider>> GetCollider(){return ColliderBox;}

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
     * @brief Set Object different movement.
     * @param idx for the character's index.
     */
    void SetVisable(const int &idx,bool isleft);

    /**
     * @brief Set Object different movement.
     * @param idx for the character's index.
     * @param visable for shoot object can see.
     */
    void SetShootVisable(const int &idx, bool visable);

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


    std::shared_ptr<AnimatedObject> CharacterAnimate;
    std::shared_ptr<ImageObject> CharacterImage;


    std::vector<std::vector<std::string>> CharacterAnimatePath;
    std::vector<std::string> CharacterShootPath;
    std::vector<std::string> CharacterImagePath;

    std::vector<std::shared_ptr<AnimatedObject>> CharacterDeath;
    std::vector<std::shared_ptr<ImageObject>> CharacterSpawn;

    std::vector<std::shared_ptr<Ammo>> Magazine;

    // timer to make animation smoothly.
    unsigned long MoveTimer = 0,ShootTimer = 0,ClimbTimer = 0;
    unsigned long DeathTimer = 0,DeathTime = 2500;

    int Health = 28;
    int Visable = 0;

    std::shared_ptr<glm::vec2> Position;
    glm::vec2 RightScale = {-3,3},LeftScale = {3,3};
    float ZIndex = 60;

    glm::vec2 Initial_Pos = {-1,-1}; //When Using Jumping module, to calculate the moving.
    glm::vec2 Ladder_Pos = {-2000,-2000}; //Initial ladder collison position.
    LiveState RockmanState;
    PhysicState MoveState;

    //Rockman's Invincible State
    bool Invincible = false;
    unsigned long InvincibleTimer = 0,InvincibleTime = 300;

    //Debug Mode Invincible
    bool DebugMode = false;
    std::vector<std::shared_ptr<Collider>> ColliderBox;


    //Music
    std::shared_ptr<Util::SFX> RockmanBGM;
};
#endif
