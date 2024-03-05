#ifndef BACK_GROUND_HPP
#define BACK_GROUND_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"


class BackGround : public Util::GameObject{
public:
    BackGround(const std::string& BackGroundPath); //Constructor
    void SetImage(const std::string& BackGroundPath);
    [[nodiscard]] const glm::vec2& GetPosition();
    void SetPosition(const glm::vec2& Position);
private:
    std::string m_BackGroundPath;
};



#endif
