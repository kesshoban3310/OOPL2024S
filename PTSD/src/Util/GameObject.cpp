#include "Util/GameObject.hpp"
#include "Util/Transform.hpp"
#include "Util/TransformUtils.hpp"
#include "config.hpp"

namespace Util {

void GameObject::Draw() {
    if (!m_Visible || m_Drawable == nullptr) {
        return;
    }

    // Check if out of screen
    glm::vec2 size = GetScaledSize();
    glm::vec2 translation = m_Transform.translation;
    if ((translation.x + size.x / 2 < WINDOW_WIDTH / -1.0) ||
        (translation.x - size.x / 2 > WINDOW_WIDTH / 1.0) ||
        (translation.y + size.y / 2 < WINDOW_HEIGHT / -1.0) ||
        (translation.y - size.y / 2 > WINDOW_HEIGHT / 1.0)) {
        return;
    }

    auto data = Util::ConvertToUniformBufferData(
        m_Transform, m_Drawable->GetSize(), m_ZIndex);
    data.m_Model = glm::translate(
        data.m_Model, glm::vec3{m_Pivot / m_Drawable->GetSize(), 0} * -1.0F);

    m_Drawable->Draw(data);
}

} // namespace Util
