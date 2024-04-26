#ifndef PHASE_MENU_HPP
#define PHASE_MENU_HPP

#include "Component/Phase.hpp"
#include "Component/ImageObject.hpp"
#include "Component/AnimatedObject.hpp"
#include "Util/BGM.hpp"

class PhaseMenu final : public Phase {
public:
    void Init(App *app) override;

    void Update(App *app) override;

    void Leave(App *app) override;

    explicit PhaseMenu(App::State lastState)
        : Phase(lastState){};

private:
    enum class Stage {
        CUTMAN = 0,
        GUTSMAN = 1,
        ICEMAN = 2,
        BOMBMAN = 3,
        FIREMAN = 4,
        ELECMAN = 5
    };
    std::unordered_map<Stage, Stage> m_NextStage;
    std::unordered_map<Stage, Stage> m_PreviousStage;
    std::unordered_map<Stage, glm::vec2> m_SelectBoxPosition;
    Stage m_Stage = Stage::CUTMAN;
    std::shared_ptr<AnimatedObject> m_Screen = nullptr;
    std::shared_ptr<AnimatedObject> m_SelectBox = nullptr;
    std::shared_ptr<Util::BGM> m_BGM = nullptr;
};

#endif // PHASE_MENU_HPP
