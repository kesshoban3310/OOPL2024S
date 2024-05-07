#include "Component/Backgroundmap.hpp"
#include "Component/TileMap.hpp"
#include "Util/Logger.hpp"
#include "config.hpp"

Backgroundmap::Backgroundmap(const std::string &stage) {
    this->stage = stage;
}

void Backgroundmap::SetImagetoBackgroundObject() {
    Map = TileMap::GetBackgroundObjects(stage);
}
void Backgroundmap::SetImagetoForegroundObject() {
    Map = TileMap::GetForegroundObjects(stage);
}
std::vector<std::shared_ptr<TileBox>>
Backgroundmap::GetCollisonBox(glm::vec2 camerapos) {
    std::vector<std::shared_ptr<TileBox>> CollisonBox;
    for (int i = 0; i < Map.size(); i++) {
        glm::vec2 pos = Map[i]->GetPosition();
        if (pos.x + 24 < camerapos.x-384 || pos.x - 24 > camerapos.x+384 ||
            pos.y + 24 < camerapos.y-360 || pos.y - 24 > camerapos.y+360)
            continue;
        CollisonBox.push_back(Map[i]);
    }
    return CollisonBox;
}
