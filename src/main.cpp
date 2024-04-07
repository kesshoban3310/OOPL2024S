#include "Component/App.hpp"
#include "Core/Context.hpp"

int main(int, char **) {
    // TODO: change to App::State::TITLE when deploy
    App app(App::State::TITLE);

    while (!app.GetContext()->GetExit()) {
        app.Update();
    }
    return 0;
}
