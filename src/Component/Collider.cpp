#include "Component/Collider.hpp"
#include "Util/Logger.hpp"
#include <cmath>
#include <utility>

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

std::set<Collider::Bound> WhereIsColliding(const Collider &self,
                                           const Collider &other) {
    // TODO: Modify algorithm to make it more clear.
    std::set<Collider::Bound> box;

    bool Left = self.GetPosition().x > other.GetPosition().x,
         Right = self.GetPosition().x <= other.GetPosition().x;
    bool Up = other.GetPosition().y >= self.GetTop() &&
              (self.GetLeft() < other.GetPosition().x &&
               other.GetPosition().x < self.GetRight()),
         Down = self.GetBottom() >= other.GetPosition().y &&
                (self.GetLeft() < other.GetPosition().x &&
                 other.GetPosition().x < self.GetRight());
    if (Up) {
        box.insert(Collider::Bound::TOP);
        return box;
    }
    if (Down) {
        box.insert(Collider::Bound::BOTTOM);
        return box;
    }
    if (Right) {
        box.insert(Collider::Bound::RIGHT);
    }
    if (Left) {
        box.insert(Collider::Bound::LEFT);
    }
    return box;
}
bool IfObjectIsOverlaping(const Collider &self, const Collider &other) {
    float Area = self.GetSize().x * self.GetSize().y;
    float OverLapArea = 0;
    float OtherXLeft = other.GetLeft(), OtherXRight = other.GetRight(),
          OtherYBottom = other.GetBottom(), OtherYTop = other.GetTop();
    float SelfXLeft = self.GetLeft(), SelfXRight = self.GetRight(),
          SelfYBottom = self.GetBottom(), SelfYTop = self.GetTop();
    float XMin = std::max(OtherXLeft, SelfXLeft),
          XMax = std::min(OtherXRight, SelfXRight),
          YMin = std::max(OtherYBottom, SelfYBottom),
          YMax = std::min(OtherYTop, SelfYTop);

    OverLapArea = (XMax - XMin) * (YMax - YMin);

    // LOG_DEBUG(std::to_string(Area));
    // LOG_DEBUG(std::to_string(OverLapArea));

    return OverLapArea / Area >= 0.25;
}
