#include "Component/Boss.hpp"
#include "Util/Time.hpp"

Boss::Boss(std::shared_ptr<std::queue<std::shared_ptr<Bomb>>> bombs,
           std::shared_ptr<std::queue<std::shared_ptr<Item>>> items,
           std::shared_ptr<Util::Renderer> renderer)
    : Enemy({12800, -2798}, RESOURCE_DIR "/Picture/Boss/Bombman/idle.png", 28,
            true, {26 * 3, 20 * 3}, Enemy::HurtState::COWARDLY, LifeState::LIFE,
            {3, 3}, {0, -10 * 3}),
      m_RandomNumberGenerator(std::random_device{}()),
      m_Bombs(std::move(bombs)),
      m_Items(std::move(items)),
      m_Renderer(std::move(renderer)) {}

void Boss::DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                      int SceneStage) {
    m_IsTriggered = 12264 <= RockmanPos.x && RockmanPos.x <= 13032 &&
                       -2300 >= RockmanPos.y && RockmanPos.y >= -3048;
    if (!m_IsTriggered)
        return;
    m_StateDuration += Util::Time::GetDeltaTimeMs();
    switch (m_State) {
    case State::Idle: {
        SetImage(RESOURCE_DIR "/Picture/Boss/Bombman/idle.png");
        if (m_StateDuration < 500)
            break;
        int randomNumber = m_RandomNumberDistribution(m_RandomNumberGenerator);
        ChangeState(State::Attack);
        if (randomNumber == 0)
            ChangeState(State::Jump);
        else
            ChangeState(State::Attack);
        if (RockmanPos.x > GetPosition().x)
            Object->SetScale({-3, 3});
        else
            Object->SetScale({3, 3});
        m_StateDuration = 0;
        break;
    }
    case State::Attack: {
        if (m_StateDuration < 150) { // 0 - 150
            SetImage(RESOURCE_DIR "/Picture/Boss/Bombman/throw1.png");
        }
        else if (m_StateDuration < 300) { // 151 - 300
            SetImage(RESOURCE_DIR "/Picture/Boss/Bombman/throw2.png");
            if (!m_IsThrown) {
                std::shared_ptr<Bomb> bomb = std::make_shared<Bomb>(
                    RESOURCE_DIR "/Picture/Bomb/Bomb.png",
                    GetPosition() + glm::vec2{0, 10 * 3}, RockmanPos,
                    -2600 + float(m_RandomNumberGenerator() % 200), 3, 3);
                m_Bombs->push(bomb);
                m_Renderer->AddChild(bomb);
                m_IsThrown = true;
            }
        }
        else
            ChangeState(State::Idle);
        break;
    }
    case State::Jump: {
        SetImage(RESOURCE_DIR "/Picture/Boss/Bombman/jump.png");
        if (!m_IsJumped) {
            auto CalculateFallingTime = [&](float startY, float endY) {
                return std::sqrt(2 * std::abs(endY - startY) * GRAVITY);
            };
            glm::vec2 startPosition = GetPosition();
            glm::vec2 expectedEndPosition = {
                std::clamp(RockmanPos.x, 12360.0f, 12936.0f), -2798.0f};
            float expectedHeight =
                -2600 + float(m_RandomNumberGenerator() % 200);
            m_XVelocity =
                (expectedEndPosition.x - startPosition.x) /
                (CalculateFallingTime(startPosition.y, expectedHeight) +
                 CalculateFallingTime(expectedHeight, expectedEndPosition.y));
            m_YVelocity =
                CalculateFallingTime(startPosition.y, expectedHeight) / GRAVITY;
            m_IsJumped = true;
        }
        glm::vec2 currentPosition = GetPosition();
        currentPosition.x += m_XVelocity * Util::Time::GetDeltaTimeMs();
        m_YVelocity -= Util::Time::GetDeltaTimeMs() / GRAVITY;
        currentPosition.y += m_YVelocity * Util::Time::GetDeltaTimeMs();
        SetPosition(currentPosition);
        if (currentPosition.y < -2798) {
            SetPosition({currentPosition.x, -2798});
            ChangeState(State::Idle);
        }
        break;
    }
    }
}

void Boss::Reset() {
    if (m_IsDead)
        return;
    ChangeState(State::Idle);
    m_IsThrown = false;
    m_IsJumped = false;
    m_StateDuration = 0;
    SetPosition({12800, -2798});
    SetImage(RESOURCE_DIR "/Picture/Boss/Bombman/idle.png");
    Object->SetScale({3, 3});
    m_XVelocity = 0;
    m_YVelocity = 0;
    SetLifeState(LifeState::LIFE);
    SetHealth(28);
    SetVisable(true);
}
