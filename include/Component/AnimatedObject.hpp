#ifndef ANIMATED_OBJECT_HPP
#define ANIMATED_OBJECT_HPP

#include <string>
#include <vector>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class AnimatedObject : public Util::GameObject {
public:
    explicit AnimatedObject(const std::vector<std::string> &ImagePaths);

    [[nodiscard]] std::vector<std::string> GetImagePaths() const;

    [[nodiscard]] const glm::vec2 &GetPosition() const;

    [[nodiscard]] bool GetVisibility() const;

    [[nodiscard]] const glm::vec2 &GetScale() const;

    void SetImages(const std::vector<std::string> &ImagePaths);

    void SetPosition(const glm::vec2 &Position);

    void SetScale(const glm::vec2 &Scale);

    void ResetPosition();

private:
    std::vector<std::string> m_ImagePaths;
};

#endif // ANIMATED_OBJECT_HPP
