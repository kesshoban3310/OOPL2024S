#ifndef PERSON_LIFE_HPP
#define PERSON_LIFE_HPP

#include "Util/GameObject.hpp"
#include "Util/Text.hpp"

class PersonLife : public Util::GameObject {
public:
    PersonLife();
    ~PersonLife() override = default;
    void Update(int life, glm::vec2 cameraPosition);

private:
    const glm::vec2 SCALE = {3, 3};
    const glm::vec2 OFFSETS[4] = {
        {-300, 320}, {-264, 320}, {-240, 320}, {-216, 320}};
    const float Z_INDEX = 80;
};

#endif
