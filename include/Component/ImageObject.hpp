#ifndef IMAGE_OBJECT_HPP
#define IMAGE_OBJECT_HPP

#include <string>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class ImageObject : public Util::GameObject {
public:
    explicit ImageObject(const std::string &ImagePath);

    [[nodiscard]] const std::string &GetImagePath() const;

    [[nodiscard]] const glm::vec2 &GetPosition() const;

    [[nodiscard]] bool GetVisibility() const;

    [[nodiscard]] const glm::vec2 &GetScale() const;

    void SetImage(const std::string &ImagePath);

    void SetPosition(const glm::vec2 &Position);

    void SetScale(const glm::vec2 &Scale);

    void ResetPosition();

private:
    std::string m_ImagePath;
};

#endif // IMAGE_OBJECT_HPP
