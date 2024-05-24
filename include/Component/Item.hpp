#ifndef ITEM_HPP
#define ITEM_HPP

#include "Component/Collider.hpp"
#include "Component/TileBox.hpp"
#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

enum class ItemType {
    SMALL_HEALTH_ENERGY,
    BIG_HEALTH_ENERGY,
    SMALL_WEAPON_ENERGY,
    BIG_WEAPON_ENERGY,
    ONE_UP,
    SPECIAL_WEAPON_ITEM,
    SCORE_BALL
};

class Item final : public Util::GameObject {
public:
    explicit Item(ItemType type, glm::vec2 position,
                  float remainingTime = 10000.0f);
    ~Item() override = default;

    [[nodiscard]] ItemType GetType() const { return m_Type; }

    [[nodiscard]] Collider GetCollider() const { return *m_Collider; }

    [[nodiscard]] bool IsAlive() const {
        return m_RemainingTime > 0.0f && !m_MarkedForRemoval;
    }

    void MarkForRemoval() { m_MarkedForRemoval = true; }

    void
    Update(std::shared_ptr<std::vector<std::shared_ptr<TileBox>>> tileBoxes);

private:
    ItemType m_Type;
    std::shared_ptr<Collider> m_Collider;
    std::shared_ptr<glm::vec2> m_Position;
    float m_RemainingTime;
    bool m_MarkedForRemoval = false;
};

#endif
