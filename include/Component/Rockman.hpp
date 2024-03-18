#ifndef ROCKMAN_HPP
#define ROCKMAN_HPP

#include "AnimatedObject.hpp"
#include "Characterattribute.hpp"
#include "pch.hpp"

class Rockman{
public:
    /**
     * @brief Constructor.
     */
    Rockman();
    /**
     * @brief Initialize the object.
     * Include all Image into this class.
     */
    void Initialize();
    /**
     * @brief Set Object different movement.
     * @param idx for the character's index.
     */
    void Setvisable(const int &idx);
    /**
     * @brief collect all object in character.
     * @return All object in character.
     */
    [[nodiscard]]std::vector<std::shared_ptr<Util::GameObject>> Getchildren() const{
        std::vector<std::shared_ptr<Util::GameObject>> children;
        for(auto i:character)
            children.push_back(i);
        return children;
    }
    /**
     * @brief Set object position.
     */
    void Setposition(glm::vec2 position);
    /**
     * @brief Get object position.
     * @return Object's postition.
     */
    glm::vec2 Getposition();
    /**
     * @brief Make Rockman Move.
     */
    void move();
private:
    std::vector<std::shared_ptr<AnimatedObject>> character;
    std::vector<bool> visable;
    glm::vec2 position = {-322,-157};
};

#endif
