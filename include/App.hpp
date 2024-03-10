#ifndef APP_HPP
#define APP_HPP

#include "Component/AnimatedObject.hpp"
#include "Component/Backgroundmap.hpp"
#include "Component/ImageObject.hpp"
#include "Component/Txtconverter.hpp"

#include "Util/GameObject.hpp"
#include "Util/Root.hpp"
#include "pch.hpp" // IWYU pragma: export

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    Util::Root m_Root;
    State m_CurrentState = State::START;


    // game objects
    std::shared_ptr<AnimatedObject> m_StartBackground;
    std::shared_ptr<ImageObject> m_Tile;

    std::shared_ptr<Backgroundmap> m_Map;
    std::shared_ptr<Txtconverter> m_converter;

};

#endif
