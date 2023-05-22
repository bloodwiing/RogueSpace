#ifndef JAGE_DYING_HPP
#define JAGE_DYING_HPP

#include "jage/node/abc/dying_abc.hpp"

namespace jage::node::base {

    class DyingBase : public abc::DyingABC {
    public:
        void kill() override;
        void kill(float delay) override;
        [[nodiscard]] bool isDead() const override;

        void updateDeathTimer();

    private:
        float m_deathTimer = 0.0f;
        bool m_dead = false;
    };
}

#endif //JAGE_DYING_HPP
