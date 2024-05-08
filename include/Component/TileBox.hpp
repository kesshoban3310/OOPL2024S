#ifndef TILE_BOX_HPP
#define TILE_BOX_HPP

#include "Component/Collider.hpp"
#include "Util/GameObject.hpp"

class TileBox {
public:
    enum class ObjectType {
        CLIMB,
        DAMAGE,
        WALL,
        NORMAL,
    };
    TileBox(glm::vec2 pos, glm::vec2 sca,
            std::shared_ptr<Util::GameObject> object, ObjectType type);
    std::shared_ptr<Util::GameObject> Getchild() { return Object; }
    std::shared_ptr<Collider> Getcollisonbox() { return collisonbox; }
    glm::vec2 GetPosition() { return *position; }
    TileBox::ObjectType GetObjectType() { return type; }

private:
    glm::vec2 scale;
    std::shared_ptr<glm::vec2> position;
    std::shared_ptr<Util::GameObject> Object;
    std::shared_ptr<Collider> collisonbox;
    ObjectType type;
};
#endif
