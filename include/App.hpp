#ifndef APP_HPP
#define APP_HPP

#include "Component/AnimatedObject.hpp"
#include "Component/Backgroundmap.hpp"
#include "Component/ImageObject.hpp"
#include "Component/Txtconverter.hpp"
#include "Component/Rockman.hpp"


#include "Util/GameObject.hpp"
#include "Util/Root.hpp"
#include "pch.hpp" // IWYU pragma: export

class App {
public:
    enum class State {
        START,
        GAME_STAGE_SELECT,
        GAME_STAGE,
        GAME_LOSE,
        ENDING_ANIMATION,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void GameStageSelect();

    void GameStage();

    void GameLose();

    void EndingAnimation();

    void End(); // NOLINT(readability-convert-member-functions-to-static)
    /** @brief return if any key pressed.
    *   @return true if no any key pressed.
    */
    bool NoKeyPress();

private:
    Util::Root m_Root;
    State m_CurrentState = State::START;

    // game objects
    std::shared_ptr<AnimatedObject> m_StartBackground;
    std::shared_ptr<ImageObject> m_Tile;

    std::shared_ptr<Backgroundmap> m_Map;
    std::shared_ptr<Txtconverter> m_Converter;

    std::shared_ptr<Rockman> m_Rockman;
    std::shared_ptr<AnimatedObject> m_animate;
};

#endif
