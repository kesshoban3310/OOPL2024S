#ifndef SMALLBOMB_HPP
#define SMALLBOMB_HPP

#include "Component/Collider.hpp"
#include "Component/EnemyAttribute.hpp"
#include "ImageObject.hpp"
#include "Util/Time.hpp"
#include "glm/fwd.hpp"
#include <cmath>
#include <memory>
#include <string>
#include <vector>

class SmallBomb :public Enemy,Physic{
public:
    SmallBomb(std::string imagePath, glm::vec2 startPosition,
              glm::vec2 expectedEndPosition, float expectedHeight,glm::vec2 storedPosition);
    void DoBehavior(glm::vec2 CameraPos,glm::vec2 RockmanPos,int SceneStage) override;
    void PhysicEngine() override;
    void TrajectCalculator();
    void Reset() override;
    void SetCanMove(bool canmove);
    bool CanBombombombMove();
private:
    const float GRAVITY = 200.0f;
    float m_XVelocity;
    float m_YVelocity;

    glm::vec2 StartPosition;
    glm::vec2 EndPosition;
    glm::vec2 StoredPosition;
    float ExpectedHeight;
    bool m_CanMove = false;
    bool m_IsMoving = false;
    bool BombombombCanMove = true;
};

#endif
