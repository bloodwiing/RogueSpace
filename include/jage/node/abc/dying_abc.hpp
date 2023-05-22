#ifndef JAGE_DYING_ABC_HPP
#define JAGE_DYING_ABC_HPP

namespace jage::node::abc {

    class DyingABC {
    public:
        virtual void kill() = 0;
        virtual void kill(float delay) = 0;
        [[nodiscard]] virtual bool isDead() const = 0;
    };
}

#endif //JAGE_DYING_ABC_HPP
