#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include "ImageObject.hpp"
#include "pch.hpp"

class HealthBar {
public:
    HealthBar(glm::vec2 pos,std::string path,int pathlength);
    void SetVisable(const int &idx);
    void SetPosition(glm::vec2 cameraposition);
    [[nodiscard]] std::shared_ptr<Util::GameObject> GetChild();
private:
    std::shared_ptr<ImageObject> Bar;
    std::vector<std::string> Path;
    glm::vec2 position;
    int index = -1;
};

#endif
