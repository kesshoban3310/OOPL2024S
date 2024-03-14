#include "Component/AnimatedObject.hpp"

AnimatedObject::AnimatedObject(const std::vector<std::string> &ImagePaths,
                               bool play, std::size_t interval, bool looping) {
    SetAnimation(ImagePaths, play, interval, looping);
    ResetPosition();
}

[[nodiscard]] std::vector<std::string> AnimatedObject::GetImagePaths() const {
    return m_ImagePaths;
}

[[nodiscard]] glm::vec2 AnimatedObject::GetPosition() const {
    return m_Transform.translation;
}

[[nodiscard]] bool AnimatedObject::GetVisibility() const {
    return m_Visible;
}

[[nodiscard]] glm::vec2 AnimatedObject::GetScale() const {
    return m_Transform.scale;
}

[[nodiscard]] bool AnimatedObject::GetLooping() const {
    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->GetLooping();
}

[[nodiscard]] int AnimatedObject::GetInterval() const {
    return std::dynamic_pointer_cast<Util::Animation>(m_Drawable)
        ->GetInterval();
}

void AnimatedObject::SetAnimation(const std::vector<std::string> &ImagePaths,
                                  bool play, std::size_t interval,
                                  bool looping) {
    m_ImagePaths = ImagePaths;
    m_Drawable =
        std::make_shared<Util::Animation>(ImagePaths, play, interval, looping);
}

void AnimatedObject::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}

void AnimatedObject::SetScale(const glm::vec2 &Scale) {
    m_Transform.scale = Scale;
}

void AnimatedObject::ResetPosition() {
    m_Transform.translation = {0, 0};
}

void AnimatedObject::SetLooping(bool looping) {
    std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->SetLooping(looping);
}

void AnimatedObject::SetInterval(std::size_t interval) {
    std::dynamic_pointer_cast<Util::Animation>(m_Drawable)
        ->SetInterval((int)interval);
}

void AnimatedObject::PlayAnimation() {
    std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->Play();
}

void AnimatedObject::ResetAnimation() {
    std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->Reset();
}

void AnimatedObject::PauseAnimation() {
    std::dynamic_pointer_cast<Util::Animation>(m_Drawable)->Pause();
}
