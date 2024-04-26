#ifndef PHASE_LOSE_HPP
#define PHASE_LOSE_HPP

#include "Component/Phase.hpp"
#include "Component/ImageObject.hpp"
#include "Util/BGM.hpp"

class PhaseLose final : public Phase {
public:
    void Init(App *app) override;

    void Update(App *app) override;

    void Leave(App *app) override;

    explicit PhaseLose(App::State lastState)
        : Phase(lastState){};

private:
    enum class State {
        CONTINUE,
        STAGE_SELECT,
    };
    State m_State = State::CONTINUE;
    std::shared_ptr<ImageObject> m_Screen;
    std::shared_ptr<Util::BGM> m_BGM;
};

#endif // PHASE_LOSE_HPP
