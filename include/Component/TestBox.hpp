#ifndef TEST_BOX_HPP
#define TEST_BOX_HPP

#include "IncludeComponent.hpp"

class TestBox {
public:
    TestBox(glm::vec2 pos, glm::vec2 sca);
    void Move();
    void SetPosition(glm::vec2 pos){
        *position = pos;
        Object->SetPosition(pos);
    }
    std::shared_ptr<Util::GameObject> Getchild() {
        std::shared_ptr<Util::GameObject> box = Object;
        return box;
    }
    std::shared_ptr<Collider> Getcollisonbox() { return collisonbox; }
    glm::vec2 GetPosition() {return *position;}
private:
    glm::vec2 scale;
    std::shared_ptr<glm::vec2> position;
    std::shared_ptr<ImageObject> Object;
    std::shared_ptr<Collider> collisonbox;
};

#endif
