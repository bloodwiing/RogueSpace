#ifndef GAME_TEST_CANVAS_HPP
#define GAME_TEST_CANVAS_HPP

#include "jage/node/canvas.hpp"

namespace game::canvas {

    class HUDCanvas {
    public:
        static std::unique_ptr<jage::node::Canvas> create();
    };
}

#endif //GAME_TEST_CANVAS_HPP
