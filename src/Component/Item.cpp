#include "Component/Item.hpp"
#include "Component/TileBox.hpp"
#include "Util/Time.hpp"
#include <string>

Item::Item(ItemType type, glm::vec2 position, float remainingTime)
    : m_Type(type),
      m_Position(std::make_shared<glm::vec2>(position)),
      m_RemainingTime(remainingTime) {
    m_Transform.translation = *m_Position;
    m_Transform.scale = {3, 3};
    const std::string folderPath = RESOURCE_DIR "/Picture/Item/";
    switch (type) {
    case ItemType::SMALL_HEALTH_ENERGY:
        m_Drawable = std::make_shared<Util::Image>(folderPath +
                                                   "Small_Health_Energy.png");
        break;
    case ItemType::BIG_HEALTH_ENERGY:
        m_Drawable = std::make_shared<Util::Animation>(
            Util::Animation({folderPath + "Big_Health_Energy_1.png",
                             folderPath + "Big_Health_Energy_2.png"},
                            true, 100));
        break;
    case ItemType::SMALL_WEAPON_ENERGY:
        m_Drawable = std::make_shared<Util::Image>(folderPath +
                                                   "Small_Weapon_Energy.png");
        break;
    case ItemType::BIG_WEAPON_ENERGY:
        m_Drawable = std::make_shared<Util::Animation>(
            Util::Animation({folderPath + "Big_Weapon_Energy_1.png",
                             folderPath + "Big_Weapon_Energy_2.png"},
                            true, 100));
        break;
    case ItemType::ONE_UP:
        m_Drawable = std::make_shared<Util::Image>(folderPath + "One_Up.png");
        break;
    case ItemType::SPECIAL_WEAPON_ITEM:
        m_Drawable = std::make_shared<Util::Animation>(
            Util::Animation({folderPath + "Special_Weapon_Item_1.png",
                             folderPath + "Special_Weapon_Item_2.png"},
                            true, 100));
        break;
    case ItemType::SCORE_BALL:
        m_Drawable =
            std::make_shared<Util::Image>(folderPath + "Score_Ball.png");
        break;
    }
    SetZIndex(70);
    m_Collider = std::make_shared<Collider>(Collider(
        m_Position, GetScaledSize() - glm::vec2{4 * 3, 4 * 3}, {0, -2 * 3}));
}

void Item::Update(
    std::shared_ptr<std::vector<std::shared_ptr<TileBox>>> tileBoxes) {
    const glm::vec2 velocity = {0, -0.2};
    m_Position->y += velocity.y * Util::Time::GetDeltaTimeMs();
    m_RemainingTime -= Util::Time::GetDeltaTimeMs();

    for (auto &tileBox : *tileBoxes) {
        Collider tileBoxCollider = *tileBox->Getcollisonbox();
        if (IsColliding(tileBoxCollider, *m_Collider)) {
            m_Position->y -= m_Collider->GetBottom() - tileBoxCollider.GetTop();
        }
    }
    m_Transform.translation = *m_Position;
}
