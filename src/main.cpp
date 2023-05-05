#include "jage/engine.hpp"

int main() {

    auto& engine = jage::JAGEngine::getInstance();
    engine.init();
    engine.loadScene();
    engine.loop();

    return 0;
}
