#include "jage/engine.hpp"

#include "jage/event/timerevent.hpp"

int main() {

    auto& engine = jage::JAGEngine::getInstance();
    engine.init();
    engine.loadScene();
    engine.loop();

    return 0;
}
