#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include "ImageObject.hpp"
#include "pch.hpp"

class Healthbar {
public:
    Healthbar(glm::vec2 pos);
    void SetVisable(const int &idx);
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren();
    void SetPosition(glm::vec2 cameraposition);

private:
    std::vector<std::shared_ptr<ImageObject>> bar;
    glm::vec2 position;
    int index = -1;
};

#endif
