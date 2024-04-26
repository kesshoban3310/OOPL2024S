#include "Component/SceneManager.hpp"
#include "config.hpp"
#include <algorithm>

SceneManager::SceneManager(std::unordered_map<int, SceneRange> sceneRanges,
                           int defaultScene)
    : m_CurrentScene(defaultScene),
      m_SceneRanges(std::move(sceneRanges)),
      m_StartChangeTime(0.0f) {}

void SceneManager::Update(glm::vec2 position) {
    // Iterate over all the scenes
    for (auto &[sceneId, sceneRange] : m_SceneRanges) {
        // Check if scene changes need to be made
        if (sceneRange.IsContain(position) && sceneId != m_CurrentScene) {
            // Set the current scene
            m_CurrentScene = sceneId;
            // Record the time and camera position of the change
            m_StartChangeTime = Util::Time::GetElapsedTimeMs();
            m_StartCameraPosition = m_CameraPosition;
            break;
        }
    }

    // Update the camera position
    auto GetUpdatedCameraPosition = [&]() -> glm::vec2 {
        // Clamp the x position to the scene bounds
        float x_min = m_SceneRanges[m_CurrentScene].m_TopLeft.x +
                      WINDOW_WIDTH / 2.0f;
        float x_max = m_SceneRanges[m_CurrentScene].m_BottomRight.x -
                      WINDOW_WIDTH / 2.0f;
        float x = std::clamp(position.x, x_min, x_max);

        // calculate the y position
        float y = (m_SceneRanges[m_CurrentScene].m_BottomRight.y +
                   m_SceneRanges[m_CurrentScene].m_TopLeft.y) /
                  2.0f;
        return {x, y};
    };
    // If the scene is changing
    if (IsChangingScene()) {
        float progress = (Util::Time::GetElapsedTimeMs() - m_StartChangeTime) /
                         SCENE_CHANGE_DELAY_MS;
        m_CameraPosition =
            m_StartCameraPosition +
            progress * (GetUpdatedCameraPosition() - m_StartCameraPosition);
    }
    else { // If the scene is not changing
        m_CameraPosition = GetUpdatedCameraPosition();
    }
}

bool SceneManager::IsChangingScene() const {
    return m_StartChangeTime + SCENE_CHANGE_DELAY_MS >
           Util::Time::GetElapsedTimeMs();
}
