#ifndef ROCKMAN_HPP
#define ROCKMAN_HPP

#include "AnimatedObject.hpp"
#include "Characterattribute.hpp"
#include "pch.hpp"

class Rockman{
public:
    Rockman();
    /**
     * @brief Initialize the object.
     * Include all Image into this class.
     */
    void Initialize();
    /**
     * @brief Set Object can see or cannot see.
     */
    void Setvisable(const int &idx);


    [[nodiscard]]std::vector<std::shared_ptr<Util::GameObject>> Getchildren() const{
        std::vector<std::shared_ptr<Util::GameObject>> children;
        for(auto i:character)
            children.push_back(i);
        return children;
    }
    void Setposition(glm::vec2 position);
    glm::vec2 Getposition();
    void move();
private:
    std::vector<std::shared_ptr<AnimatedObject>> character;
    std::vector<bool> visable;
    glm::vec2 position = {-322,-157};
};

#endif
