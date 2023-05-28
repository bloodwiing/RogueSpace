#ifndef GAME_GAME_SCENE_HPP
#define GAME_GAME_SCENE_HPP

#include "jage/node/scene.hpp"

namespace game::scene {

    class GameScene {
    public:
        static std::unique_ptr<jage::node::Scene> create();
    };
}

#endif //GAME_GAME_SCENE_HPP
