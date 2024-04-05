#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "pch.hpp"

class Collider {
public:
    Collider(std::shared_ptr<glm::vec2> position, glm::vec2 size,
             glm::vec2 offset);

    friend bool IsColliding(const Collider &self, const Collider &other);

    [[nodiscard]] glm::vec2 GetPosition() const;

    [[nodiscard]] glm::vec2 GetSize() const;

    [[nodiscard]] glm::vec2 GetOffset() const;

private:
    [[nodiscard]] inline float GetTop() const;
    [[nodiscard]] inline float GetBottom() const;
    [[nodiscard]] inline float GetLeft() const;
    [[nodiscard]] inline float GetRight() const;

    std::shared_ptr<glm::vec2> m_Position;
    glm::vec2 m_Offset;
    glm::vec2 m_Size;
};

#endif // COLLIDER_HPP
