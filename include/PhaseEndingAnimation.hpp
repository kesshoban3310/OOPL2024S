#ifndef PHASE_ENDING_ANIMATION_HPP
#define PHASE_ENDING_ANIMATION_HPP

#include "Component/AnimatedObject.hpp"
#include "Component/ImageObject.hpp"
#include "Component/Phase.hpp"
#include "Util/GameObject.hpp"
#include "Util/BGM.hpp"

class PhaseEndingAnimation : public Phase {
public:
    void Init(App *app) override;

    void Update(App *app) override;

    void Leave(App *app) override;

    explicit PhaseEndingAnimation(App::State lastState)
        : Phase(lastState){};

private:
    bool m_IsScrolling = false;
    std::shared_ptr<ImageObject> m_Background = nullptr;
    std::shared_ptr<Util::GameObject> m_Character = nullptr;
    std::shared_ptr<Util::BGM> m_BGM = nullptr;
};

#endif // PHASE_ENDING_ANIMATION_HPP
