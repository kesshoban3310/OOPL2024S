#include "App.hpp"

#include "Core/Context.hpp"

int main(int, char **) {
    std::shared_ptr<Core::Context> context = Core::Context::GetInstance();
    App app;

    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
        case App::State::START:
            app.Start();
            break;

        case App::State::GAME_STAGE_SELECT:
            app.GameStageSelect();
            break;

        case App::State::GAME_STAGE:
            app.GameStage();
            break;

        case App::State::GAME_LOSE:
            app.GameLose();
            break;

        case App::State::ENDING_ANIMATION:
            app.EndingAnimation();
            break;

        case App::State::END:
            app.End();
            context->SetExit(true);
            break;
        }
        context->Update();
    }
    return 0;
}
