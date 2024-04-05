#ifndef PHASE_HPP
#define PHASE_HPP

#include "App.hpp"

class Phase {
public:
    virtual void Init(App *app) = 0;

    virtual void Update(App *app) = 0;

    virtual void Leave(App *app) = 0;

    explicit Phase(App::State lastState);

    Phase() = default;

    ~Phase() = default;

protected:
    [[nodiscard]] App::State GetLastState() const;

private:
    App::State m_LastState;
};

#endif // PHASE_HPP
