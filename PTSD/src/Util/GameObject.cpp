#include "Util/GameObject.hpp"
#include "config.hpp"

namespace Util {

void GameObject::Draw(const glm::vec2 &offset) {
    if (!m_Visible) {
        return;
    }

    // Apply offset
    Util::Transform transform = m_Transform;
    transform.translation += offset;

    // Check if out of screen
    glm::vec2 size = GetScaledSize();
    if ((transform.translation.x + size.x / 2 < WINDOW_WIDTH / -2.0) ||
        (transform.translation.x - size.x / 2 > WINDOW_WIDTH / 2.0) ||
        (transform.translation.y + size.y / 2 < WINDOW_HEIGHT / -2.0) ||
        (transform.translation.y - size.y / 2 > WINDOW_HEIGHT / 2.0)) {
        return;
    }

    m_Drawable->Draw(transform, m_ZIndex);
}

} // namespace Util
