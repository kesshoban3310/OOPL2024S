//
// Created by User on 2024/4/19.
//
#include "Component/TileBox.hpp"

TileBox::TileBox(glm::vec2 pos, glm::vec2 sca, std::shared_ptr<Util::GameObject> object, TileBox::ObjectType type) {
    this->scale = sca;
    this->Object = object;
    this->type = type;
    this->position = std::make_shared<glm::vec2>(pos);
    if(type == TileBox::ObjectType::CLIMB)
        this->collisonbox = std::make_shared<Collider>(this->position, glm::vec2{16 * 3, 16 * 3}, glm::vec2{0, 0});
    else
        this->collisonbox = std::make_shared<Collider>(this->position, glm::vec2{16 * 3, 16 * 3}, glm::vec2{0, 0});
}