#ifndef BACK_GROUND_IMAGE_HPP
#define BACK_GROUND_IMAGE_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"


class BackGroundImage : public Util::GameObject{
public:
    BackGroundImage(const std::string& BackGroundPath); //Constructor
    void SetImage(const std::string& BackGroundPath);
    [[nodiscard]] const glm::vec2& GetPosition();
    void SetPosition(const glm::vec2& Position);
private:
    std::string m_BackGroundPath;
};


#endif
