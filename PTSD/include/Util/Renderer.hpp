#ifndef UTIL_RENDERER_HPP
#define UTIL_RENDERER_HPP

#include <memory>
#include <vector>

#include "Util/GameObject.hpp"

class App;

namespace Util {
class Renderer final {
public:
    /**
     * @brief Parameterized constructor.
     *
     * @param children The GameObject needing to be managed by the renderer.
     */
    explicit Renderer(
        const std::vector<std::shared_ptr<GameObject>> &children = {});

    /**
     * @brief Add a child to the renderer.
     *
     * @param child The GameObject needing to be managed by the renderer.
     */
    void AddChild(const std::shared_ptr<GameObject> &child);

    /**
     * @brief Add children to the renderer.
     *
     * @param children The GameObjects needing to be managed by the renderer.
     */
    void AddChildren(const std::vector<std::shared_ptr<GameObject>> &children);

    /**
     * @brief Remove the child from the renderer.
     *
     * @param child The GameObject being removed.
     */
    void RemoveChild(std::shared_ptr<GameObject> child);

    /**
     * @brief Remove children.
     *
     * @param children The GameObjects being removed.
     */
    void
    RemoveChildren(const std::vector<std::shared_ptr<GameObject>> &children);

    /**
     * @brief All GameObjects in the renderer will be removed.
     */
    void RemoveAllChildren();

    /**
     * @brief Draw children according to their z-index.
     *
     * @note The user is not recommended to modify this function.
     */
    void Update(const glm::vec2 &renderOffset = {0.0f, 0.0f});

private:
    std::vector<std::shared_ptr<GameObject>> m_Children;
};
} // namespace Util

#endif // UTIL_RENDERER_HPP
