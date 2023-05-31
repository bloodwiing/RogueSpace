#include "jage/script/actor/bulletscript.hpp"

using jage::script::actor::BulletScript;

BulletScript::BulletScript(abc::ScriptableABC* node, jage::Tag tagFilter, float radius, float damage)
        : CollisionNotifierScript(node, tagFilter, radius)
        , m_damage(damage)
{

}

float BulletScript::getDamage() const {
    return m_damage;
}
