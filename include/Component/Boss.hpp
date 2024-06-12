#ifndef BOSS_HPP
#define BOSS_HPP

#include "Component/Bomb.hpp"
#include "Component/EnemyAttribute.hpp"
#include "Component/Item.hpp"
#include "Util/Renderer.hpp"
#include <queue>
#include <random>

class Boss : public Enemy {
public:
    Boss(std::shared_ptr<std::queue<std::shared_ptr<Bomb>>> bombs,
         std::shared_ptr<std::queue<std::shared_ptr<Item>>> items,
         std::shared_ptr<Util::Renderer> renderer);
    ~Boss() override = default;

    void DoBehavior(glm::vec2 CameraPos, glm::vec2 RockmanPos,
                    int SceneStage) override;
    void Reset() override;

    [[nodiscard]] bool IsTriggered() const { return m_IsTriggered; }

private:
    enum class State { Idle, Attack, Jump };
    void ChangeState(State newState) {
        m_State = newState;
        // reset values
        m_StateDuration = 0.0f;
        m_IsThrown = false;
        m_IsJumped = false;
    }

    float m_StateDuration = 0.0f;
    std::mt19937 m_RandomNumberGenerator;
    std::uniform_int_distribution<int> m_RandomNumberDistribution =
        std::uniform_int_distribution<int>(0, 1);
    State m_State = State::Idle;
    bool m_IsThrown = false;
    bool m_IsJumped = false;
    bool m_IsTriggered = false;
    const float GRAVITY = 250.0f;
    float m_XVelocity = 0.0f;
    float m_YVelocity = 0.0f;
    std::shared_ptr<std::queue<std::shared_ptr<Bomb>>> m_Bombs;
    std::shared_ptr<std::queue<std::shared_ptr<Item>>> m_Items;
    std::shared_ptr<Util::Renderer> m_Renderer;
};

#endif
