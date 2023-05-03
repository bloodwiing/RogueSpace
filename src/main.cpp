#include "engine/engine.hpp"

int main() {

    auto& engine = Engine::JAGEngine::getInstance();
    engine.init();
    engine.loadScene();
    engine.loop();

    return 0;
}
