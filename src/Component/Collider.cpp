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
    /* Definition of this function.
     * Basic from self side.
     * For example, when return Collider::Bound::TOP, It means self's top
     * crashed.
     */
    std::set<Collider::Bound> box;
    glm::vec2 SelfPos = self.GetPosition();
    float SelfLeft = self.GetLeft(), SelfRight = self.GetRight();
    float SelfTop = self.GetTop(), SelfBottom = self.GetBottom();

    glm::vec2 OtherPos = other.GetPosition();
    float OtherLeft = other.GetLeft(), OtherRight = other.GetRight();
    float OtherTop = other.GetTop(), OtherBottom = other.GetBottom();

    if (SelfLeft <= OtherRight && OtherLeft <= SelfRight &&
        SelfBottom <= OtherTop && OtherBottom <= SelfTop) {
        float XOverlap,YOVerlap;
        if(SelfBottom <= OtherTop && OtherTop <= SelfTop){
            YOVerlap = (OtherTop-SelfBottom)/(OtherTop-OtherBottom);
        }
        else{
            YOVerlap = (SelfTop-OtherBottom)/(OtherTop-OtherBottom);
        }
        if(OtherLeft <= SelfRight && SelfRight <= OtherRight){
            XOverlap = (SelfRight-OtherLeft)/(OtherRight-OtherLeft);
        }
        else{
            XOverlap = (OtherRight-SelfLeft)/(OtherRight-OtherLeft);
        }
        if( YOVerlap>=0.15 ) {
            if (OtherLeft <= SelfLeft &&
                SelfLeft <= OtherRight) { // Self Left Collide
                box.insert(Collider::Bound::LEFT);
            }
            if (OtherLeft <= SelfRight &&
                SelfRight <= OtherRight) { // Self Right Collide
                box.insert(Collider::Bound::RIGHT);
            }
        }
        else if(XOverlap>=0.15){
            if (OtherBottom <= SelfTop &&
                SelfTop <= OtherTop) { // Self Top Collide
                box.insert(Collider::Bound::TOP);
            }
            if (OtherBottom <= SelfBottom &&
                SelfBottom <= OtherTop) { // Self Bottom Collide
                box.insert(Collider::Bound::BOTTOM);
            }
        }
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
