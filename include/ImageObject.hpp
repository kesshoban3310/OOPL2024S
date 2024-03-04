#ifndef IMAGEOBJECT_HPP
#define IMAGEOBJECT_HPP

#include <string>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class ImageObject : public Util::GameObject {
public:
    explicit ImageObject(const std::string &ImagePath) {
        SetImage(ImagePath);
        ResetPosition();
    }

    [[nodiscard]] const std::string &GetImagePath() const {
        return m_ImagePath;
    }

    [[nodiscard]] const glm::vec2 &GetPosition() const {
        return m_Transform.translation;
    }

    [[nodiscard]] bool GetVisibility() const { return m_Visible; }

    void SetImage(const std::string &ImagePath) {
        m_ImagePath = ImagePath;
        m_Drawable = std::make_shared<Util::Image>(m_ImagePath);
    }

    void SetPosition(const glm::vec2 &Position) {
        m_Transform.translation = Position;
    }

    void SetScale(const glm::vec2 &Scale) { m_Transform.scale = Scale; }
    void ResetPosition() { m_Transform.translation = {0, 0}; }

private:
    std::string m_ImagePath;
};

#endif // IMAGEOBJECT_HPP
