#ifndef JAGE_BULLET_SCRIPT_HPP
#define JAGE_BULLET_SCRIPT_HPP

#include "jage/script/actor/collidisionnotifierscript.hpp"
#include "jage/node/actor/dynamicactor.hpp"

namespace jage::script::actor {

    class BulletScript
            : public CollisionNotifierScript
    {
    public:
        BulletScript(abc::ScriptableABC* node, Tag tagFilter, float radius, float damage);

        [[nodiscard]] float getDamage() const;

    private:
        float m_damage;
    };
}

#endif //JAGE_BULLET_SCRIPT_HPP
