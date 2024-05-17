#include "Component/Backgroundmap.hpp"
#include "Component/Tilemap.hpp"
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
std::vector<std::shared_ptr<TileBox>> Backgroundmap::GetTileBox() {
    return Map;
}
