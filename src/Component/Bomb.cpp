#include "Component/Bomb.hpp"
#include "Util/Animation.hpp"
#include "Util/Time.hpp"

Bomb::Bomb(const std::string &imagePath, glm::vec2 startPosition,
           glm::vec2 expectedEndPosition, float expectedHeight) {

    auto CalculateFallingTime = [&](float startY, float endY) {
        return std::sqrt(2 * std::abs(endY - startY) * GRAVITY);
    };

    m_Drawable = std::make_shared<Util::Image>(imagePath);
    m_Transform.scale = {3, 3};
    m_Position = std::make_shared<glm::vec2>(startPosition);
    SetZIndex(70);
    m_XVelocity = (expectedEndPosition.x - startPosition.x) /
                  (CalculateFallingTime(startPosition.y, expectedHeight) +
                   CalculateFallingTime(expectedHeight, expectedEndPosition.y));
    m_YVelocity =
        CalculateFallingTime(startPosition.y, expectedHeight) / GRAVITY;
    m_Collider = std::make_shared<Collider>(m_Position, GetScaledSize(),
                                            glm::vec2{0, 0});
    m_Transform.translation = *m_Position;
}

void Bomb::Update(
    std::shared_ptr<std::vector<std::shared_ptr<TileBox>>> tiles) {
    if (m_State == State::FALLING) {
        m_Position->x += m_XVelocity * Util::Time::GetDeltaTimeMs();
        m_YVelocity -= Util::Time::GetDeltaTimeMs() / GRAVITY;
        m_Position->y += m_YVelocity * Util::Time::GetDeltaTimeMs();
        m_Transform.translation = *m_Position;

        for (const auto &tile : *tiles) {
            if (IsColliding(*tile->Getcollisonbox(), *m_Collider)) {
                SetToExplode();
                break;
            }
        }
    }
    if (m_State == State::EXPLODING &&
        std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetState() ==
            Util::Animation::State::ENDED) {
        m_MarkedForRemoval = true;
    }
}

void Bomb::SetToExplode() {
    m_State = State::EXPLODING;
    m_Drawable = std::make_shared<Util::Animation>(
        std::vector<std::string>{
            RESOURCE_DIR "/Picture/Bomb/Explosion_1.png",
            RESOURCE_DIR "/Picture/Bomb/Explosion_2.png",
            RESOURCE_DIR "/Picture/Bomb/Explosion_3.png",
            RESOURCE_DIR "/Picture/Bomb/Explosion_4.png",
        },
        true, 70, false);
}
