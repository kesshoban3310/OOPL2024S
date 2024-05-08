//
// Created by User on 2024/3/27.
//

#include "Component/HealthBar.hpp"
#include "Util/Logger.hpp"
// "/Picture/Character/Health/blood"
HealthBar::HealthBar(glm::vec2 pos,std::string path,int pathlength) {
    this->position = {pos.x - 311, pos.y + 201};
    this->index = pathlength-1;
    for (int i = pathlength; i >= 1; i--) {
        std::string healthpath = RESOURCE_DIR + path + std::to_string(i) + ".png";
        Path.push_back(healthpath);
    }
    Bar = std::make_shared<ImageObject>(Path[pathlength-1]);
    Bar->SetPosition(position);
    Bar->SetScale({3, 3});
    Bar->SetZIndex(70);
    Bar->SetVisible(true);
}
std::shared_ptr<Util::GameObject> HealthBar::GetChild() {
    std::shared_ptr<Util::GameObject> Object = Bar;
    return Object;
}
void HealthBar::SetVisable(const int &idx) {
    if (idx == -1) {
        return;
    }
    index = idx;
    Bar->SetImage(Path[index]);
}
void HealthBar::SetPosition(glm::vec2 cameraposition) {
    Bar->SetPosition(cameraposition);
    position = cameraposition;
}
