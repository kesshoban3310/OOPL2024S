#include "Component/ImageObject.hpp"

ImageObject::ImageObject(const std::string &ImagePath) {
    SetImage(ImagePath);
    ResetPosition();
}

[[nodiscard]] const std::string &ImageObject::GetImagePath() const {
    return m_ImagePath;
}

[[nodiscard]] const glm::vec2 &ImageObject::GetPosition() const {
    return m_Transform.translation;
}

[[nodiscard]] bool ImageObject::GetVisibility() const {
    return m_Visible;
}

[[nodiscard]] const glm::vec2 &ImageObject::GetScale() const {
    return m_Transform.scale;
}

void ImageObject::SetImage(const std::string &ImagePath) {
    m_ImagePath = ImagePath;
    m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
}

void ImageObject::SetPosition(const glm::vec2 &Position) {
    m_Transform.translation = Position;
}

void ImageObject::SetScale(const glm::vec2 &Scale) {
    m_Transform.scale = Scale;
}

void ImageObject::ResetPosition() {
    m_Transform.translation = {0, 0};
}
