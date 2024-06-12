#include "Component/Backgroundmap.hpp"

Backgroundmap::Backgroundmap(const std::string &stage) {
    this->stage = stage;
}

void Backgroundmap::SetImagetoBackgroundObject() {
    Map = TileMap::GetBackgroundObjects(stage);
}
void Backgroundmap::SetImagetoForegroundObject() {
    Map = TileMap::GetForegroundObjects(stage);
}
std::vector<std::shared_ptr<TileBox>> Backgroundmap::GetTileBox() {
    return Map;
}
