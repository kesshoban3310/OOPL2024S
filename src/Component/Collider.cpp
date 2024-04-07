#include <utility>

#include "Component/Collider.hpp"

Collider::Collider(std::shared_ptr<glm::vec2> position, glm::vec2 size,
                   glm::vec2 offset = {0, 0})
    : m_Position(std::move(position)),
      m_Offset(offset),
      m_Size(size) {}

glm::vec2 Collider::GetPosition() const {
    return *m_Position;
}

glm::vec2 Collider::GetSize() const {
    return m_Size;
}

glm::vec2 Collider::GetOffset() const {
    return m_Offset;
}

float Collider::GetTop() const {
    return m_Position->y + m_Offset.y + m_Size.y / 2;
}

float Collider::GetBottom() const {
    return m_Position->y + m_Offset.y - m_Size.y / 2;
}

float Collider::GetLeft() const {
    return m_Position->x + m_Offset.x - m_Size.x / 2;
}

float Collider::GetRight() const {
    return m_Position->x + m_Offset.x + m_Size.x / 2;
}

bool IsColliding(const Collider &self, const Collider &other) {
    return self.GetLeft() <= other.GetRight() &&
           other.GetLeft() <= self.GetRight() &&
           self.GetBottom() <= other.GetTop() &&
           other.GetBottom() <= self.GetTop();
}
