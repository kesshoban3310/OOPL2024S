#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "pch.hpp"

class Collider {
public:
    enum class Bound {
        LEFT,
        RIGHT,
        TOP,
        BOTTOM,
    };
    Collider(std::shared_ptr<glm::vec2> position, glm::vec2 size,
             glm::vec2 offset);
    friend bool IsColliding(const Collider &self, const Collider &other);
    friend std::set<Collider::Bound> WhereIsColliding(const Collider &self,
                                                         const Collider &other);
    friend bool IfObjectIsOverlaping(const Collider &self,
                                  const Collider &other);
    [[nodiscard]] glm::vec2 GetPosition() const;

    [[nodiscard]] glm::vec2 GetSize() const;

    [[nodiscard]] glm::vec2 GetOffset() const;
    [[nodiscard]] float GetTop() const;
    [[nodiscard]] float GetBottom() const;
    [[nodiscard]] float GetLeft() const;
    [[nodiscard]] float GetRight() const;
private:


    std::shared_ptr<glm::vec2> m_Position;
    glm::vec2 m_Offset;
    glm::vec2 m_Size;
};

#endif // COLLIDER_HPP
