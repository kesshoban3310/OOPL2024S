#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "Util/Time.hpp"
#include "glm/glm.hpp"
#include <unordered_map>
#include <utility>

// TODO: implement the camera part
/**
 * @brief Scene manager class, handle for camera position and scene change
 */
class SceneManager {
public:
    struct SceneRange {
        glm::vec2 m_TopLeft;
        glm::vec2 m_BottomRight;

        /**
         * @brief Check if the position is in the scene
         *
         * @param position Position to check
         * @return true if the position is in the scene
         * @return false if the position is not in the scene
         */
        [[nodiscard]] bool IsContain(glm::vec2 position) const {
            return position.x >= m_TopLeft.x && position.x <= m_BottomRight.x &&
                   position.y <= m_TopLeft.y && position.y >= m_BottomRight.y;
        }
    };

    SceneManager() = default;
    ~SceneManager() = default;

    /**
     * @brief Constructor for SceneManager object
     *
     * @param scenePositions Scene positions for each scene
     * @param defaultScene Default scene number
     */
    explicit SceneManager(std::unordered_map<int, SceneRange> sceneRanges,
                          int defaultScene = 0);

    /**
     * @brief Update the current scene by player's position
     *
     * @param position Player's position
     *
     * @return position of camera
     */
    void Update(glm::vec2 position);

    /**
     * @brief Check if the scene is changing
     *
     * @return true if the scene is changing
     * @return false if the scene is not changing
     */
    bool IsChangingScene() const;

    /**
     * @brief Set the scene ranges
     *
     * @param sceneRanges Scene ranges
     */
    void SetSceneRanges(std::unordered_map<int, SceneRange> sceneRanges) {
        m_SceneRanges = std::move(sceneRanges);
    }

    /**
     * @brief Get the current scene
     *
     * @return Current scene number
     */
    [[nodiscard]] int GetCurrentScene() const { return m_CurrentScene; }

    /**
     * @brief Get the camera position
     *
     * @return Camera position
     */
    [[nodiscard]] glm::vec2 GetCameraPosition() const {
        return m_CameraPosition;
    }

    /**
     * @brief Check if the position is falling out of the scene
     *
     * @param position Position to check
     * @param threshold Tolerance of the position to check
     *
     * @return true if the position is falling out of the scene
     * @return false if the position is not falling out of the scene
     */
    bool IsFallOutOfScene(glm::vec2 position, float threshold = 200.0f) const;

private:
    static constexpr unsigned int SCENE_CHANGE_DELAY_MS = 1000;
    int m_CurrentScene = 0;
    std::unordered_map<int, SceneRange> m_SceneRanges = {};
    glm::vec2 m_CameraPosition = glm::vec2(0.0f, 0.0f);

    // the start time of changing scene, only used when m_SceneChanging is true
    float m_StartChangeTime = 0.0f;
    // the start camera position of changing scene, only used when
    // m_SceneChanging is true
    glm::vec2 m_StartCameraPosition = glm::vec2(0.0f, 0.0f);
};

#endif
