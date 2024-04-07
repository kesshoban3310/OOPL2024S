#include "Component/Backgroundmap.hpp"
#include "Component/TileMap.hpp"
#include "Util/Logger.hpp"
#include "config.hpp"

Backgroundmap::Backgroundmap(const std::string &stage) {
    this->stage = stage;
}

void Backgroundmap::SetImagetoBackgroundObject() {
    Map = TileMap::GetBackgroundObjects(stage);
    // TODO IDK if we should this
    // SetObjectCollisonBox();
}
void Backgroundmap::SetImagetoForegroundObject() {
    Map = TileMap::GetForegroundObjects(stage);
    SetObjectCollisonBox();
}
void Backgroundmap::SetObjectCollisonBox() {
    for (auto i : Map) {
        std::shared_ptr<glm::vec2> position =
            std::make_shared<glm::vec2>(i->GetPosition());
        std::shared_ptr<Collider> Collisonbox;
        if (i->GetImagePath() ==
            (RESOURCE_DIR "/Picture/Tiles/Bomb Man Stage/Object/15.png"))
            Collisonbox = std::make_shared<Collider>(
                position, glm::vec2{8 * 3, 8 * 3}, glm::vec2{0, 0});
        else
            Collisonbox = std::make_shared<Collider>(
                position, glm::vec2{16 * 3, 16 * 3}, glm::vec2{0, 0});
        MapCollisonBox.push_back(Collisonbox);
    }
}
