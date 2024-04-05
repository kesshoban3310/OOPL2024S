//
// Created by User on 2024/3/27.
//

#include "Component/Healthbar.hpp"
#include "Util/Logger.hpp"


Healthbar::Healthbar(glm::vec2 pos) {
    this->position = {pos.x-311,pos.y+201};
    for(int i=29;i>=1;i--){
        std::string path = RESOURCE_DIR "/Picture/Character/Health/blood" +
                           std::to_string(i) + ".png";
        std::shared_ptr<ImageObject> bar = std::make_shared<ImageObject>(path);
        bar->SetPosition(position);
        bar->SetScale({3,3});
        bar->SetZIndex(70);
        bar->SetVisible(false);
        this->bar.push_back(bar);
    }
}
std::vector<std::shared_ptr<Util::GameObject>> Healthbar::GetChildren() {
    std::vector<std::shared_ptr<Util::GameObject>> Object;
    for(auto i:bar){
        Object.push_back(i);
    }
    return Object;
}
void Healthbar::SetVisable(const int &idx) {
    if(index == -1){
        index = idx;
        bar[idx]->SetVisible(true);
        return;
    }
    bar[idx]->SetVisible(true);
    bar[index]->SetVisible(false);
    index = idx;
}
void Healthbar::SetPosition(glm::vec2 cameraposition) {
    bar[index]->SetPosition({cameraposition.x-311,cameraposition.y+201});
    position = cameraposition;
}