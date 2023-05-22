#include "jage/node/base/dying_base.hpp"

#include "jage/runtime/time.hpp"

using jage::node::base::DyingBase;

void DyingBase::kill() {
    m_dead = true;
}

void DyingBase::kill(float delay) {
    m_deathTimer = delay;
}

bool DyingBase::isDead() const {
    return m_dead;
}

void DyingBase::update() {
    using jage::runtime::Time;

    if (m_deathTimer > 0.0f and !m_dead) {
        m_deathTimer -= Time::getDeltaFloat();
        if (m_deathTimer < 0.0f) {
            m_dead = true;
            m_deathTimer = 0.0f;
        }
    }
}
