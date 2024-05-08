#ifndef SCOREBAR_HPP
#define SCOREBAR_HPP

#include "Component/ImageObject.hpp"
#include "pch.hpp"

class Scorebar {
public:
    Scorebar(glm::vec2 pos);
    void AddScore(int point);
    void Show(glm::vec2 pos);
    [[nodiscard]] std::vector<std::shared_ptr<Util::GameObject>> GetChildren() {
        return scoreObject;
    }

private:
    std::vector<int> score = std::vector<int>(7, 0);
    std::vector<std::shared_ptr<ImageObject>> scoreImage;
    std::vector<std::shared_ptr<Util::GameObject>> scoreObject;
    glm::vec2 position;
    glm::vec2 scale = {3, 3};
    float ZIndex = 70;
};

#endif
