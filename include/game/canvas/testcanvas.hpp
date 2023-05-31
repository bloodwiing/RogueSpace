#ifndef GAME_TEST_CANVAS_HPP
#define GAME_TEST_CANVAS_HPP

#include "jage/node/canvas.hpp"
#include "jage/node/scene.hpp"

namespace game::canvas {

    class TestCanvas {
    public:
        static std::unique_ptr<jage::node::Canvas> create(jage::node::Scene* scene);
    };
}

#endif //GAME_TEST_CANVAS_HPP
