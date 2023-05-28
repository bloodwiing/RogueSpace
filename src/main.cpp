#include "jage/engine.hpp"
#include "game/scene/gamescene.hpp"

int main() {

    auto& engine = jage::JAGEngine::getInstance();
    engine.init();
    engine.loadScene(game::scene::GameScene::create);
    engine.loop();

    return 0;
}
