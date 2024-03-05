#include "Component/AnimatedObject.hpp"

AnimatedObject::AnimatedObject(const std::vector<std::string> &ImagePaths) {
    SetImages(ImagePaths);
    ResetPosition();
}

[[nodiscard]] std::vector<std::string> AnimatedObject::GetImagePaths() const {
    return m_ImagePaths;
}

[[nodiscard]] const glm::vec2 &AnimatedObject::GetPosition() const {
    return m_Transform.translation;
}

[[nodiscard]] bool AnimatedObject::GetVisibility() const {
    return m_Visible;
}

[[nodiscard]] const glm::vec2 &AnimatedObject::GetScale() const {
    return m_Transform.scale;
}

void AnimatedObject::SetImages(const std::vector<std::string> &ImagePaths) {
    m_ImagePaths = ImagePaths;
    m_Drawable = std::make_shared<Util::Animation>(ImagePaths, true, 500);
}

void AnimatedObject::SetPosition(const glm::vec2 &Position) {
    m_Transform.scale = Position;
}

void AnimatedObject::SetScale(const glm::vec2 &Scale) {
    m_Transform.scale = Scale;
}

void AnimatedObject::ResetPosition() {
    m_Transform.translation = {0, 0};
}
