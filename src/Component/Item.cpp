#include "Component/Item.hpp"
#include <string>

Item::Item(ItemType type, glm::vec2 position)
    : m_Type(type) {
    m_Transform.translation = position;
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
    m_Collider = std::make_shared<Collider>(
        Collider(std::make_shared<glm::vec2>(m_Transform.translation),
                 GetScaledSize(), {0, 0}));
}
