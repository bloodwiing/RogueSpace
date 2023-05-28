#include "jage/engine.hpp"
#include "game/scene/gamescene.hpp"
#include "game/canvas/hudcanvas.hpp"

int main() {

    auto& engine = jage::JAGEngine::getInstance();
    engine.init();
    engine.loadScene(game::scene::GameScene::create);
    engine.loadCanvas(game::canvas::HUDCanvas::create);
    engine.loop();

    return 0;
}
