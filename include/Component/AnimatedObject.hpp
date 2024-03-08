#ifndef ANIMATED_OBJECT_HPP
#define ANIMATED_OBJECT_HPP

#include <string>
#include <vector>

#include "Util/Animation.hpp"
#include "Util/GameObject.hpp"

class AnimatedObject : public Util::GameObject {
public:
    explicit AnimatedObject(const std::vector<std::string> &ImagePaths,
                            bool play, std::size_t interval,
                            bool looping = true);

    [[nodiscard]] std::vector<std::string> GetImagePaths() const;

    [[nodiscard]] glm::vec2 GetPosition() const;

    [[nodiscard]] bool GetVisibility() const;

    [[nodiscard]] glm::vec2 GetScale() const;

    [[nodiscard]] bool GetLooping() const;

    [[nodiscard]] int GetInterval() const;

    void SetAnimation(const std::vector<std::string> &ImagePaths, bool play,
                      std::size_t interval, bool looping = true);

    void SetPosition(const glm::vec2 &Position);

    void SetScale(const glm::vec2 &Scale);

    void ResetPosition();

    void SetLooping(bool looping);

    void SetInterval(std::size_t interval);

    void PlayAnimation();

    void ResetAnimation();

    void PauseAnimation();

private:
    std::vector<std::string> m_ImagePaths;
};

#endif // ANIMATED_OBJECT_HPP
